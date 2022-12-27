//
// Created by lebonq on 20/12/22.
//

#include "Map.hpp"

Map::Map(const std::string& nameLevel)
{
    DEBUG_PRINT("Create a Map " << std::endl);
    std::ifstream json_file(nameLevel + ".json");
    this->m_data = json::parse(json_file);

    this->m_nLevels      = this->m_data["levels"].size();
    this->m_currentLevel = 0;
    this->loadMap(this->m_data["levels"]["0"]["image"]);

    DEBUG_PRINT(this->m_data["levels"].size() << std::endl);
    this->initWorldObject();
    this->initInteractiveObject();

    // set starting pos player
    int pos_player = this->getEntrancePos();
    int cam_x      = pos_player % this->getWidth();
    int cam_z      = (pos_player - cam_x) / this->getWidth();

    this->m_player = new Player(cam_x, cam_z, cam_x, cam_z, this->getHeight(), this->getWidth());
}

void Map::loadMap(const std::string& nameLevel)
{
    int               width, height;
    std::vector<uint> image_data = Util::readImageFile(nameLevel, &width, &height);
    this->m_width                = width;
    this->m_height               = height;

    int cpt = 0;
    this->m_terrain.clear();
    for (auto datum : image_data) {
        switch (datum) {
        case DM_PROJECT_COLOR_WALL:
            this->m_terrain.push_back(DM_PROJECT_MAP_WALL);
            break;
        case DM_PROJECT_COLOR_EMPTY:
            this->m_terrain.push_back(DM_PROJECT_MAP_EMPTY);
            break;
        case DM_PROJECT_COLOR_DOOR:
            this->m_terrain.push_back(DM_PROJECT_MAP_DOOR);
            break;
        case DM_PROJECT_COLOR_WATER:
            this->m_terrain.push_back(DM_PROJECT_MAP_WATER);
            break;
        case DM_PROJECT_COLOR_ENTRANCE:
            this->m_terrain.push_back(DM_PROJECT_MAP_ENTRANCE);
            this->m_entrancePos = cpt;
            break;
        case DM_PROJECT_COLOR_EXIT:
            this->m_terrain.push_back(DM_PROJECT_MAP_EXIT);
            this->m_exitPos = cpt;
            break;
        default:
            PRINT("Bad image for map.");
            exit(-1);
        }
        cpt++;
    }
}

Map::~Map()
{
    DEBUG_PRINT("Delete a Map " << std::endl);
    for (auto& worldObject : this->m_worldObjects) {
        delete worldObject;
    }
    for (auto& worldItem : this->m_worldItems) {
        delete worldItem;
    }
    for (auto& worldMonster : this->m_worldMonsters) {
        delete worldMonster;
    }
    delete this->m_player;
}

void Map::initWorldObject()
{
    int index_right = 0;
    int index_bot   = 0;
    int index       = 0;

    this->m_worldObjects.clear();

    Model*    wall = this->m_ModelsManager.getRefModel(DM_PROJECT_ID_MANAGER_WALL);
    glm::mat4 wallMatrix(1);
    glm::mat4 floorMatrix(1);
    glm::mat4 waterMatrix(1);

    wallMatrix = glm::translate(wallMatrix, glm::vec3(0, 0.5, 0.5));
    for (int y = 0; y < this->m_height; y++) {
        for (int x = 0; x < this->m_width; x++) {
            index       = y * this->m_width + x;
            index_right = index + 1;
            index_bot   = index + this->m_width;

            wallMatrix = glm::translate(wallMatrix, glm::vec3(1, 0, 0));

            // For real wall facing X
            if (this->m_terrain[index_bot] != DM_PROJECT_MAP_WALL && this->m_terrain[index] == DM_PROJECT_MAP_WALL)
                this->m_worldObjects.push_back(new WorldObject(DM_PROJECT_MAP_WALL, wall, wallMatrix, x, y));
            // || index_bot >= this->m_width*this->m_height  is for when we touch the border of the map to make sure we draw our wall
            // Si index n'est pas un mur et que index_bot est un mur ou hors du tableau alors on draw
            if (this->m_terrain[index] != DM_PROJECT_MAP_WALL && (this->m_terrain[index_bot] == DM_PROJECT_MAP_WALL || y + 1 >= this->m_height)) {
                wallMatrix = glm::rotate(wallMatrix, glm::radians(180.0f), glm::vec3(0, 1, 0)); // Those rotation allow us to orient the wall inside the room
                this->m_worldObjects.push_back(new WorldObject(DM_PROJECT_MAP_WALL, wall, wallMatrix, x, y));
                wallMatrix = glm::rotate(wallMatrix, glm::radians(-180.0f), glm::vec3(0, 1, 0));
            }

            // For wall bewteen water and floor
            wallMatrix = glm::translate(wallMatrix, glm::vec3(0, -1, 0));
            if (this->m_terrain[index] != DM_PROJECT_MAP_WATER && this->m_terrain[index_bot] == DM_PROJECT_MAP_WATER)
                this->m_worldObjects.push_back(new WorldObject(DM_PROJECT_MAP_WALL, wall, wallMatrix, x, y));
            if ((this->m_terrain[index_bot] != DM_PROJECT_MAP_WATER || y + 1 >= this->m_height) && this->m_terrain[index] == DM_PROJECT_MAP_WATER) {
                wallMatrix = glm::rotate(wallMatrix, glm::radians(180.0f), glm::vec3(0, 1, 0)); // Those rotation allow us to orient the wall inside the room
                this->m_worldObjects.push_back(new WorldObject(DM_PROJECT_MAP_WALL, wall, wallMatrix, x, y));
                wallMatrix = glm::rotate(wallMatrix, glm::radians(-180.0f), glm::vec3(0, 1, 0));
            }
            wallMatrix = glm::translate(wallMatrix, glm::vec3(0, 1, 0));

            // Wall touching the top
            if (y == 0 && this->m_terrain[index] != DM_PROJECT_MAP_WALL) {
                wallMatrix = glm::translate(wallMatrix, glm::vec3(0, 0, -1));
                this->m_worldObjects.push_back(new WorldObject(DM_PROJECT_MAP_WALL, wall, wallMatrix, x, y));
                if (this->m_terrain[index] == DM_PROJECT_MAP_WATER) {
                    wallMatrix = glm::translate(wallMatrix, glm::vec3(0, -1, 0));
                    this->m_worldObjects.push_back(new WorldObject(DM_PROJECT_MAP_WALL, wall, wallMatrix, x, y));
                    wallMatrix = glm::translate(wallMatrix, glm::vec3(0, 1, 0));
                }
                wallMatrix = glm::translate(wallMatrix, glm::vec3(0, 0, 1));
            }

            // Wall facing Z
            wallMatrix = glm::rotate(wallMatrix, glm::radians(90.0f), glm::vec3(0, 1, 0));
            wallMatrix = glm::translate(wallMatrix, glm::vec3(0.5, 0, 0.5));
            // x -(y*width)
            if (this->m_terrain[index_right] != DM_PROJECT_MAP_WALL && this->m_terrain[index] == DM_PROJECT_MAP_WALL)
                this->m_worldObjects.push_back(new WorldObject(DM_PROJECT_MAP_WALL, wall, wallMatrix, x, y));
            //|| x+1 >= this->m_width) To check is we are  on the right side of the maze
            if (this->m_terrain[index] != DM_PROJECT_MAP_WALL && (this->m_terrain[index_right] == DM_PROJECT_MAP_WALL || x + 1 >= this->m_width)) {
                wallMatrix = glm::rotate(wallMatrix, glm::radians(180.0f), glm::vec3(0, 1, 0));
                this->m_worldObjects.push_back(new WorldObject(DM_PROJECT_MAP_WALL, wall, wallMatrix, x, y));
                wallMatrix = glm::rotate(wallMatrix, glm::radians(-180.0f), glm::vec3(0, 1, 0));
            }

            if (x == 0 && this->m_terrain[index] != DM_PROJECT_MAP_WALL) {
                wallMatrix = glm::translate(wallMatrix, glm::vec3(0, 0, -1));
                this->m_worldObjects.push_back(new WorldObject(DM_PROJECT_MAP_WALL, wall, wallMatrix, x, y));
                if (this->m_terrain[index] == DM_PROJECT_MAP_WATER) {
                    wallMatrix = glm::translate(wallMatrix, glm::vec3(0, -1, 0));
                    this->m_worldObjects.push_back(new WorldObject(DM_PROJECT_MAP_WALL, wall, wallMatrix, x, y));
                    wallMatrix = glm::translate(wallMatrix, glm::vec3(0, 1, 0));
                }
                wallMatrix = glm::translate(wallMatrix, glm::vec3(0, 0, 1));
            }

            // Florr to water
            wallMatrix = glm::translate(wallMatrix, glm::vec3(0, -1, 0));
            if (this->m_terrain[index] != DM_PROJECT_MAP_WATER && this->m_terrain[index_right] == DM_PROJECT_MAP_WATER)
                this->m_worldObjects.push_back(new WorldObject(DM_PROJECT_MAP_WALL, wall, wallMatrix, x, y));
            if ((this->m_terrain[index_right] != DM_PROJECT_MAP_WATER || x + 1 >= this->m_width) && this->m_terrain[index] == DM_PROJECT_MAP_WATER) {
                wallMatrix = glm::rotate(wallMatrix, glm::radians(180.0f), glm::vec3(0, 1, 0)); // Those rotation allow us to orient the wall inside the room
                this->m_worldObjects.push_back(new WorldObject(DM_PROJECT_MAP_WALL, wall, wallMatrix, x, y));
                wallMatrix = glm::rotate(wallMatrix, glm::radians(-180.0f), glm::vec3(0, 1, 0));
            }
            wallMatrix = glm::translate(wallMatrix, glm::vec3(0, 1, 0));

            wallMatrix = glm::translate(wallMatrix, glm::vec3(-0.5, 0, -0.5));
            wallMatrix = glm::rotate(wallMatrix, glm::radians(-90.0f), glm::vec3(0, 1, 0));
        }
        wallMatrix = glm::translate(wallMatrix, glm::vec3(-this->m_width, 0, 1));
    }

    // draw floor
    Model* floor = this->m_ModelsManager.getRefModel(DM_PROJECT_ID_MANAGER_FLOOR);

    for (int y = 0; y < this->m_height; y++) {
        for (int x = 0; x < this->m_width; x++) {
            index       = y * this->m_width + x;
            floorMatrix = glm::translate(floorMatrix, glm::vec3(1, 0, 0));
            if (this->m_terrain[index] == DM_PROJECT_MAP_EMPTY ||
                this->m_terrain[index] == DM_PROJECT_MAP_ENTRANCE ||
                this->m_terrain[index] == DM_PROJECT_MAP_EXIT ||
                this->m_terrain[index] == DM_PROJECT_MAP_WATER) {
                if (this->m_terrain[index] != DM_PROJECT_MAP_WATER)
                    this->m_worldObjects.push_back(new WorldObject(DM_PROJECT_MAP_EMPTY, floor, floorMatrix, x, y));
                floorMatrix = glm::translate(floorMatrix, glm::vec3(0, 1, 0));
                floorMatrix = glm::rotate(floorMatrix, glm::radians(180.0f), glm::vec3(1, 0, 0)); // Make the floor face downward
                this->m_worldObjects.push_back(new WorldObject(DM_PROJECT_MAP_EMPTY, floor, floorMatrix, x, y));
                floorMatrix = glm::rotate(floorMatrix, glm::radians(-180.0f), glm::vec3(1, 0, 0));
                floorMatrix = glm::translate(floorMatrix, glm::vec3(0, -1, 0));
            }
        }
        floorMatrix = glm::translate(floorMatrix, glm::vec3(-this->m_width, 0, 1));
    }
    floor->unBindModel();

    // Draw Water
    Model* water = this->m_ModelsManager.getRefModel(DM_PROJECT_ID_MANAGER_WATER);

    waterMatrix = glm::translate(waterMatrix, glm::vec3(0, -0.25, 0));
    for (int y = 0; y < this->m_height; y++) {
        for (int x = 0; x < this->m_width; x++) {
            index       = y * this->m_width + x;
            waterMatrix = glm::translate(waterMatrix, glm::vec3(1, 0, 0));
            if (this->m_terrain[index] == DM_PROJECT_MAP_WATER) {
                this->m_worldObjects.push_back(new WorldObject(DM_PROJECT_MAP_WATER, water, waterMatrix, x, y));
            }
        }
        waterMatrix = glm::translate(waterMatrix, glm::vec3(-this->m_width, 0, 1));
    }
}

void Map::initInteractiveObject()
{
    this->m_worldItems.clear();
    json   listItems = this->m_data["levels"][std::to_string(this->m_currentLevel)]["items"];
    Model* shadow    = this->m_ModelsManager.getRefModel(DM_PROJECT_ID_MANAGER_SHADOW);
    for (auto item : listItems) {
        Model*    item_model = this->m_ModelsManager.getRefModel(item["id_model"]);
        int       x          = item["pos_x"];
        int       y          = item["pos_y"];
        glm::mat4 mmatrix(1.0f);
        mmatrix = glm::translate(mmatrix, glm::vec3(x + 1, 0.40, y));
        glm::mat4 smatrix(1.0f);
        smatrix = glm::translate(smatrix, glm::vec3(x + 1, 0.01f, y));
        this->m_worldObjects.push_back(new WorldObject(DM_PROJECT_MAP_SHADOW, shadow, smatrix, x, y));
        Item* item_ptr = new Item(item_model, mmatrix, this->m_worldObjects.back(), x, y, item["type"], item["amount_0"], item["amount_1"]);
        this->m_worldItems.push_back(item_ptr);
        DEBUG_PRINT("Item type : " << item["type"] << " x : " << item["pos_x"] << " y : " << item["pos_y"] << std::endl);
    }

    json listMonsters = this->m_data["levels"][std::to_string(this->m_currentLevel)]["monsters"];

    for (auto monster : listMonsters) {
        Model*    monster_model = this->m_ModelsManager.getRefModel(monster["id_model"]);
        int       x             = monster["pos_x"];
        int       y             = monster["pos_y"];
        glm::mat4 mmatrix(1.0f);
        mmatrix = glm::translate(mmatrix, glm::vec3(x + 1, 0.52, y));
        glm::mat4 smatrix(1.0f);
        smatrix = glm::translate(smatrix, glm::vec3(x + 1, 0.01f, y));
        this->m_worldObjects.push_back(new WorldObject(DM_PROJECT_MAP_SHADOW, shadow, smatrix, x, y));
        Monster* monster_ptr = new Monster(monster_model, mmatrix, this->m_worldObjects.back(), x, y, monster["type"], monster["live"], monster["defense"], monster["attack"]);
        this->m_worldMonsters.push_back(monster_ptr);
        DEBUG_PRINT("Monster type : " << monster["type"] << " x : " << monster["pos_x"] << " y : " << monster["pos_y"] << std::endl);
    }
}

void Map::drawStatic()
{
    for (WorldObject* object : this->m_worldObjects) {
        if (object == nullptr) {
            DEBUG_PRINT("object of nullptr" << std::endl)
        }

        object->draw();
    }
}
void Map::drawFacing()
{
    for (Item* item : this->m_worldItems) {
        item->draw(this->m_player);
    }
    for (Monster* monster : this->m_worldMonsters) {
        monster->draw(this->m_player);
    }
}
void Map::update()
{
    int p_x = this->m_player->getMapX();
    int p_y = this->m_player->getMapY();

    for (auto monster : this->m_worldMonsters) {
        int m_x = monster->getMapX();
        int m_y = monster->getMapY();

        // id monster is 4-adjencency of player
        if ((abs(p_x - m_x) == 0 && abs(p_y - m_y) == 1) || (abs(p_x - m_x) == 1 && abs(p_y - m_y) == 0)) {
            m_player->getAttacked(monster);
        }
        else {
            int direction_x = p_x < m_x ? -1 : p_x > m_x ? 1
                                                         : 0;
            int direction_y = p_y > m_y ? 1 : p_y < m_y ? -1
                                                        : 0;

            int cell_dir_x = m_y * this->getWidth() + m_x + direction_x;
            int cell_dir_y = (m_y + direction_y) * this->getWidth() + m_x;

            //Si la case vers laquelle on veut se déplacé n'est pas vide OU que l'on en vient
            if((this->m_terrain[cell_dir_x] != DM_PROJECT_MAP_EMPTY && this->m_terrain[cell_dir_x] != DM_PROJECT_MAP_ENTRANCE && this->m_terrain[cell_dir_x] != DM_PROJECT_MAP_EXIT)
                || monster->getPreviousCell() == cell_dir_x){
                direction_x*=-1;// alors inverse la direction
               cell_dir_x = m_y * this->getWidth() + m_x + direction_x;
               //(Si cette nouvelle direct n'est pas vide OU que elle n'est pas sur la même ligne) ET que on ne veut pas se deaplcer en verticale
               if(((this->m_terrain[cell_dir_x] != DM_PROJECT_MAP_EMPTY && this->m_terrain[cell_dir_x] != DM_PROJECT_MAP_ENTRANCE && this->m_terrain[cell_dir_x] != DM_PROJECT_MAP_EXIT) || m_x+direction_x < 0 || m_x+direction_x >= this->getWidth())
                   && direction_y == 0 ){
                    srand(time(0));
                    direction_y = (rand()%3)-1;//alors on se deplace en verticale dans une direction aléatoire
               }
            }

            if((this->m_terrain[cell_dir_y] != DM_PROJECT_MAP_EMPTY && this->m_terrain[cell_dir_y] != DM_PROJECT_MAP_ENTRANCE && this->m_terrain[cell_dir_y] != DM_PROJECT_MAP_EXIT)
                || monster->getPreviousCell() == cell_dir_y){
                direction_y*=-1;//inverse la direction
               cell_dir_y = (m_y + direction_y) * this->getWidth() + m_x;
               if(((this->m_terrain[cell_dir_y] != DM_PROJECT_MAP_EMPTY && this->m_terrain[cell_dir_y] != DM_PROJECT_MAP_ENTRANCE && this->m_terrain[cell_dir_y] != DM_PROJECT_MAP_EXIT) || m_y+direction_y < 0 || m_y+direction_y >= this->getHeight())
                   && direction_x == 0 ){
                    srand(time(0));
                    direction_x = (rand()%3)-1;
               }
            }

            if (direction_x != 0 && m_x+direction_x >= 0 && m_x+direction_x < this->getWidth() &&
                (this->m_terrain[cell_dir_x] == DM_PROJECT_MAP_EMPTY || this->m_terrain[cell_dir_x] == DM_PROJECT_MAP_ENTRANCE || this->m_terrain[cell_dir_x] == DM_PROJECT_MAP_EXIT)) {
                monster->moveOnX(direction_x);
            }
            else if(m_y + direction_y >= 0 && m_y + direction_y < this->getHeight() &&
                (this->m_terrain[cell_dir_y] == DM_PROJECT_MAP_EMPTY || this->m_terrain[cell_dir_y] == DM_PROJECT_MAP_ENTRANCE || this->m_terrain[cell_dir_y] == DM_PROJECT_MAP_EXIT)) {
                monster->moveOnY(direction_y);
            }
            monster->setPreviousCell(m_y * this->getWidth() + m_x);

        }
    }
    DEBUG_PRINT("Player stats : Gold => " << std::to_string(this->m_player->getGold()) << " Life => "
                                          << std::to_string(this->m_player->getLife()) << " Defense => "
                                          << std::to_string(this->m_player->getDefense()) << " Attack => "
                                          << std::to_string(this->m_player->getAttack()) << " X =>"
                                          << std::to_string(this->m_player->getMapX()) << " Y =>" << std::to_string(this->m_player->getMapY()) << std::endl)
}
void Map::interact()
{
    int x = this->m_player->getMapX();
    int y = this->m_player->getMapY();

    // get the pos where the player look
    glm::vec3 frontVec = this->m_player->getCamera()->getFrontVector();
    float     xDir     = round(frontVec.x);
    float     yDir     = round(frontVec.z);

    x += xDir;
    y += yDir;

    for (auto it = m_worldItems.begin(); it != m_worldItems.end();) {
        Item* item = *it;
        if (item->getMapX() == x && item->getMapY() == y) {
            item->getClicked(this->m_player);
            it = m_worldItems.erase(it);
            // remove associed shadow
            for (auto it_sha = m_worldObjects.begin(); it_sha != m_worldObjects.end();) {
                WorldObject* object = *it_sha;
                if (object->getMapX() == x && object->getMapY() == y && object->getType() == DM_PROJECT_MAP_SHADOW) {
                    m_worldObjects.erase(it_sha);
                    break;
                }
                else {
                    ++it_sha;
                }
            }
            delete item;
        }
        else {
            ++it;
            DEBUG_PRINT("No item to interact with" << std::endl);
        }
    }
    for (auto it = m_worldMonsters.begin(); it != m_worldMonsters.end();) {
        Monster* monster = *it;
        if (monster->getMapX() == x && monster->getMapY() == y) {
            monster->getClicked(this->m_player);
            monster->getAttacked(this->m_player);
            DEBUG_PRINT("Monster stats : Life => " << std::to_string(monster->getLife()) << " Defense => "
                                                   << std::to_string(monster->getDefense()) << " Attack => "
                                                   << std::to_string(monster->getAttack()) << std::endl)
            if (monster->getLife() <= 0) {
                it = m_worldMonsters.erase(it);
                // remove associed shadow
                for (auto it_sha = m_worldObjects.begin(); it_sha != m_worldObjects.end();) {
                    WorldObject* object = *it_sha;
                    if (object->getMapX() == x && object->getMapY() == y && object->getType() == DM_PROJECT_MAP_SHADOW) {
                        m_worldObjects.erase(it_sha);
                        break;
                    }
                    else {
                        ++it_sha;
                    }
                }
                delete monster;
            }
            else {
                ++it;
            }
        }
        else {
            DEBUG_PRINT("No monster to interact with" << std::endl);
            it++;
        }
    }
}
