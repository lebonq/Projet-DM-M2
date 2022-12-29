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

    this->startPlayerPosComputation();
}

void Map::startPlayerPosComputation()
{
    // set starting pos player
    int pos_player = this->getEntrancePos();
    int cam_x      = pos_player % this->getWidth();
    int cam_z      = (pos_player - cam_x) / this->getWidth();

    if (this->m_player == nullptr) {
        this->m_player = new Player(cam_x, cam_z, cam_x, cam_z, this->getHeight(), this->getWidth());
    }
    else {
        this->m_player->moveLevel(cam_x, cam_z, cam_x, cam_z, this->getHeight(), this->getWidth());
    }
    this->m_player->rotateLeftCamera(0); // update lookat
}

void Map::changeLevel(int direction)
{
    this->m_currentLevel += direction;
    // Si on est deja au RDC on ne fait rien
    if (this->m_currentLevel < 0) {
        this->m_currentLevel = 0;
        this->m_message = "You are already at the ground floor";
        this->m_printMessage = true;
        return;
    }
    // si on est deja tout en haut on fini le jeu
    if (this->m_currentLevel >= this->m_nLevels) {
        this->m_currentLevel = this->m_nLevels - 1;
        this->m_message = "You have finished the game! Congrats !";
        this->m_gameFinished = true;
        this->m_printMessage = true;
        return;
    }
    this->m_message = "You are now at level " + std::to_string(this->m_currentLevel);
    this->m_printMessage = true;
    this->loadMap(this->m_data["levels"][std::to_string(this->m_currentLevel)]["image"]);
    this->initWorldObject();
    this->initInteractiveObject();
    this->startPlayerPosComputation();
    DEBUG_PRINT("Load level " << this->m_currentLevel << std::endl);
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
    for (auto& interactiveObject : this->m_interactiveObjects) {
        delete interactiveObject;
    }
    delete this->m_player;

}

void Map::initWorldObject()
{
    int index_right = 0;
    int index_bot   = 0;
    int index       = 0;

    for (auto& worldObject : this->m_worldObjects) {
        delete worldObject;
    }
    this->m_worldObjects.clear();

    Model*    wall = this->m_ModelsManager.getRefModel(DM_PROJECT_ID_MANAGER_WALL);
    glm::mat4 wallMatrix(1);
    glm::mat4 floorMatrix(1);
    glm::mat4 waterMatrix(1);
    glm::mat4 smatrix(1.0f);//MMatrix for the ladder shadow
    int x_sha = 0;
    int y_sha = 0;

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
            // Floor under the hole of entrance facing X
            if (this->m_terrain[index] == DM_PROJECT_MAP_ENTRANCE) {
                wallMatrix = glm::rotate(wallMatrix, glm::radians(180.0f), glm::vec3(0, 1, 0)); // Those rotation allow us to orient the wall inside the room
                this->m_worldObjects.push_back(new WorldObject(DM_PROJECT_MAP_WALL, wall, wallMatrix, x, y));
                wallMatrix = glm::rotate(wallMatrix, glm::radians(-180.0f), glm::vec3(0, 1, 0));
                wallMatrix = glm::translate(wallMatrix, glm::vec3(0, 0, -1));
                this->m_worldObjects.push_back(new WorldObject(DM_PROJECT_MAP_WALL, wall, wallMatrix, x, y));
                wallMatrix = glm::translate(wallMatrix, glm::vec3(0, 0, 1));
            }

            // Floor Above the hole of exit facing X
            if (this->m_terrain[index] == DM_PROJECT_MAP_EXIT) {
                wallMatrix = glm::translate(wallMatrix, glm::vec3(0, 2, 0));
                wallMatrix = glm::rotate(wallMatrix, glm::radians(180.0f), glm::vec3(0, 1, 0)); // Those rotation allow us to orient the wall inside the room
                this->m_worldObjects.push_back(new WorldObject(DM_PROJECT_MAP_WALL, wall, wallMatrix, x, y));
                wallMatrix = glm::rotate(wallMatrix, glm::radians(-180.0f), glm::vec3(0, 1, 0));
                wallMatrix = glm::translate(wallMatrix, glm::vec3(0, 0, -1));
                this->m_worldObjects.push_back(new WorldObject(DM_PROJECT_MAP_WALL, wall, wallMatrix, x, y));
                wallMatrix = glm::translate(wallMatrix, glm::vec3(0, 0, 1));
                wallMatrix = glm::translate(wallMatrix, glm::vec3(0, -2, 0));
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

            // Floor under the hole of entrance facing Z
            if (this->m_terrain[index] == DM_PROJECT_MAP_ENTRANCE) {
                wallMatrix = glm::rotate(wallMatrix, glm::radians(-180.0f), glm::vec3(0, 1, 0)); // Those rotation allow us to orient the wall inside the room
                this->m_worldObjects.push_back(new WorldObject(DM_PROJECT_MAP_WALL, wall, wallMatrix, x, y));
                wallMatrix = glm::rotate(wallMatrix, glm::radians(180.0f), glm::vec3(0, 1, 0));
                wallMatrix = glm::translate(wallMatrix, glm::vec3(0, 0, -1));
                this->m_worldObjects.push_back(new WorldObject(DM_PROJECT_MAP_WALL, wall, wallMatrix, x, y));
                wallMatrix = glm::translate(wallMatrix, glm::vec3(0, 0, 1));
            }

            // Floor above the hole of exit facing Z
            if (this->m_terrain[index] == DM_PROJECT_MAP_EXIT) {
                wallMatrix = glm::translate(wallMatrix, glm::vec3(0, 2, 0));
                wallMatrix = glm::rotate(wallMatrix, glm::radians(-180.0f), glm::vec3(0, 1, 0)); // Those rotation allow us to orient the wall inside the room
                this->m_worldObjects.push_back(new WorldObject(DM_PROJECT_MAP_WALL, wall, wallMatrix, x, y));
                wallMatrix = glm::rotate(wallMatrix, glm::radians(180.0f), glm::vec3(0, 1, 0));
                wallMatrix = glm::translate(wallMatrix, glm::vec3(0, 0, -1));
                this->m_worldObjects.push_back(new WorldObject(DM_PROJECT_MAP_WALL, wall, wallMatrix, x, y));
                wallMatrix = glm::translate(wallMatrix, glm::vec3(0, 0, 1));
                wallMatrix = glm::translate(wallMatrix, glm::vec3(0, -2, 0));
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
                // We place the floor
                if (this->m_terrain[index] == DM_PROJECT_MAP_ENTRANCE) {
                    Model* hole = this->m_ModelsManager.getRefModel(DM_PROJECT_ID_MANAGER_FLOOR_HOLE);
                    this->m_worldObjects.push_back(new WorldObject(DM_PROJECT_MAP_ENTRANCE, hole, floorMatrix, x, y));
                }
                else if (this->m_terrain[index] != DM_PROJECT_MAP_WATER)
                    this->m_worldObjects.push_back(new WorldObject(DM_PROJECT_MAP_EMPTY, floor, floorMatrix, x, y));

                // Place Ladder
                if (this->m_terrain[index] == DM_PROJECT_MAP_EXIT) {
                    Model* ladder  = this->m_ModelsManager.getRefModel(DM_PROJECT_ID_MANAGER_LADDER);
                    this->m_ladder = new Ladder(DM_PROJECT_ID_MANAGER_LADDER, ladder, floorMatrix, x, y);
                    smatrix = glm::translate(smatrix, glm::vec3(x + 1, 0.01f, y));
                    x_sha = x;
                    y_sha = y;
                }

                // We place the ceiling
                floorMatrix = glm::translate(floorMatrix, glm::vec3(0, 1, 0));
                floorMatrix = glm::rotate(floorMatrix, glm::radians(180.0f), glm::vec3(1, 0, 0)); // Make the floor face downward
                if (this->m_terrain[index] == DM_PROJECT_MAP_EXIT) {
                    Model* hole = this->m_ModelsManager.getRefModel(DM_PROJECT_ID_MANAGER_FLOOR_HOLE);
                    this->m_worldObjects.push_back(new WorldObject(DM_PROJECT_MAP_EXIT, hole, floorMatrix, x, y));
                }
                else
                    this->m_worldObjects.push_back(new WorldObject(DM_PROJECT_MAP_EMPTY, floor, floorMatrix, x, y));
                floorMatrix = glm::rotate(floorMatrix, glm::radians(-180.0f), glm::vec3(1, 0, 0));
                floorMatrix = glm::translate(floorMatrix, glm::vec3(0, -1, 0));
            }
        }
        floorMatrix = glm::translate(floorMatrix, glm::vec3(-this->m_width, 0, 1));
    }

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
    Model*    shadow = this->m_ModelsManager.getRefModel(DM_PROJECT_ID_MANAGER_SHADOW);
    this->m_worldObjects.push_back(new WorldObject(DM_PROJECT_MAP_SHADOW, shadow, smatrix, x_sha, y_sha));
}

void Map::initInteractiveObject()
{
    for (auto& interactiveObject : this->m_interactiveObjects) {
        delete interactiveObject;
    }
    this->m_interactiveObjects.clear();
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
        this->m_interactiveObjects.push_back(item_ptr);
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
        this->m_interactiveObjects.push_back(monster_ptr);
        DEBUG_PRINT("Monster type : " << monster["type"] << " x : " << monster["pos_x"] << " y : " << monster["pos_y"] << std::endl);
    }

    json listDoors = this->m_data["levels"][std::to_string(this->m_currentLevel)]["doors"];

    for (auto door : listDoors) {
        Model*    door_model = this->m_ModelsManager.getRefModel(DM_PROJECT_ID_MANAGER_DOOR);
        int       x          = door["pos_x"];
        int       y          = door["pos_y"];
        glm::mat4 mmatrix(1.0f);
        mmatrix        = glm::translate(mmatrix, glm::vec3(x + 1, 0.50, y));
        Door* door_ptr = new Door(door_model, mmatrix, x, y, door["price"]);
        this->m_interactiveObjects.push_back(door_ptr);
        DEBUG_PRINT("Door type : " << door["type"] << " x : " << door["pos_x"] << " y : " << door["pos_y"] << std::endl);
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
    //On draw uniquement les portes
    for (auto objectFacing : this->m_interactiveObjects) {
        if((dynamic_cast<const Door*>(objectFacing) != nullptr) )objectFacing->draw(this->m_player);
    }
}

void Map::drawFacing()
{
    Player* p = this->m_player;
    //on trie les objets et monstre par leur distance au joueur, cela permet de gerer la transparence correctement
    std::sort(begin(this->m_interactiveObjects),
          end(this->m_interactiveObjects),
          [p](const InteractiveObject* o1,const InteractiveObject* o2){ return sqrt(pow(p->getMapX() - o1->getMapX(), 2) + pow(p->getMapY() - o1->getMapY(), 2)) > sqrt(pow(p->getMapX() - o2->getMapX(), 2) + pow(p->getMapY() - o2->getMapY(),  2)); });

    this->m_ladder->draw();
    //on ne draw pas les portes
    for (auto objectFacing : this->m_interactiveObjects) {
        if((dynamic_cast<const Door*>(objectFacing) == nullptr) )objectFacing->draw(this->m_player);
    }
}

void Map::update(double current_time)
{
    // Manage movement and monster attackinga
    // if 1 second has passed we update monster position
    if (current_time - this->m_monsterPreviousTime > 1000)
        for (auto o : this->m_interactiveObjects) {
            if(!(dynamic_cast<const Monster*>(o) != nullptr))continue;

            Monster* monster = dynamic_cast<Monster*>(o);

            int p_x = this->m_player->getMapX();
            int p_y = this->m_player->getMapY();
            int m_x = monster->getMapX();
            int m_y = monster->getMapY();

            // if monster is 4-adjencency of player or onto the player
            if ((abs(p_x - m_x) == 0 && abs(p_y - m_y) == 1) || (abs(p_x - m_x) == 1 && abs(p_y - m_y) == 0) || (p_x == m_x && p_y == m_y)) {
                int lifeBefore = this->m_player->getLife();
                m_player->getAttacked(monster); // player get attacked
                int lifeAfter = this->m_player->getLife();
                this->m_message = "You loose " + std::to_string(lifeBefore - lifeAfter) + " hp";
                this->m_printMessage = true;
                this->m_playerIsHit = true;
            }
            else {
                // le monstre ne se deplace que si il est a 6 de distance maximum (distance cartesienne)
                float distance = sqrt(pow(p_x - m_x, 2) + pow(p_y - m_y, 2));
                if (distance >= 60) {
                    continue;
                }

                int direction_x = p_x < m_x ? -1 : p_x > m_x ? 1
                                                             : 0;
                int direction_y = p_y > m_y ? 1 : p_y < m_y ? -1
                                                            : 0;

                int cell_dir_x = m_y * this->getWidth() + m_x + direction_x;
                int cell_dir_y = (m_y + direction_y) * this->getWidth() + m_x;

                // Si la case vers laquelle on veut se déplacé n'est pas vide OU que la porte est fermée OU que l'on en vient
                if ((this->m_terrain[cell_dir_x] != DM_PROJECT_MAP_EMPTY && this->m_terrain[cell_dir_x] != DM_PROJECT_MAP_ENTRANCE && this->m_terrain[cell_dir_x] != DM_PROJECT_MAP_EXIT) || isDoorOpenAtCell(cell_dir_x) == false || monster->getPreviousCell() == cell_dir_x) {
                    direction_x *= -1; // alors inverse la direction
                    cell_dir_x = m_y * this->getWidth() + m_x + direction_x;
                    //(Si cette nouvelle direct n'est pas vide OU que la porte est fermée OU que elle n'est pas sur la même ligne) ET que on ne veut pas se deaplcer en verticale
                    if (((this->m_terrain[cell_dir_x] != DM_PROJECT_MAP_EMPTY && this->m_terrain[cell_dir_x] != DM_PROJECT_MAP_ENTRANCE && this->m_terrain[cell_dir_x] != DM_PROJECT_MAP_EXIT) || isDoorOpenAtCell(cell_dir_x) == false || m_x + direction_x < 0 || m_x + direction_x >= this->getWidth()) && direction_y == 0) {
                        direction_y = -(monster->getPreviousCell() - cell_dir_y) / this->getHeight(); // On force le deplacement vertical dans le sens opposé d'ou l'on vient
                    }
                }

                if ((this->m_terrain[cell_dir_y] != DM_PROJECT_MAP_EMPTY && this->m_terrain[cell_dir_y] != DM_PROJECT_MAP_ENTRANCE && this->m_terrain[cell_dir_y] != DM_PROJECT_MAP_EXIT) || isDoorOpenAtCell(cell_dir_y) == false || monster->getPreviousCell() == cell_dir_y) {
                    direction_y *= -1; // inverse la direction
                    cell_dir_y = (m_y + direction_y) * this->getWidth() + m_x;
                    if (((this->m_terrain[cell_dir_y] != DM_PROJECT_MAP_EMPTY && this->m_terrain[cell_dir_y] != DM_PROJECT_MAP_ENTRANCE && this->m_terrain[cell_dir_y] != DM_PROJECT_MAP_EXIT) || isDoorOpenAtCell(cell_dir_y) == false || m_y + direction_y < 0 || m_y + direction_y >= this->getHeight()) && direction_x == 0) {
                        direction_x = -(monster->getPreviousCell() - cell_dir_x);
                    }
                }

                if (canItGoThere(m_x + direction_x, m_y) && direction_x != 0) {
                    monster->moveOnX(direction_x);
                }
                else if (canItGoThere(m_x, m_y + direction_y) && direction_y != 0) {
                    monster->moveOnY(direction_y);
                }
                monster->setPreviousCell(m_y * this->getWidth() + m_x);
            }
            this->m_monsterPreviousTime = current_time;
        }

    for (auto obj : this->m_interactiveObjects) {
        if((dynamic_cast<const Door*>(obj) == nullptr) )continue;
        Door* door = dynamic_cast<Door*>(obj);
        door->update(current_time);
    }

    this->m_player->update();

    if(*this->m_player->getDeadPtr()){
        this->m_message = "You died. Press R to restart";
        this->m_printMessage = true;
    }

    /*    DEBUG_PRINT("Player stats : Gold => " << std::to_string(this->m_player->getGold()) << " Life => "
                                              << std::to_string(this->m_player->getLife()) << " Defense => "
                                              << std::to_string(this->m_player->getDefense()) << " Attack => "
                                              << std::to_string(this->m_player->getAttack()) << " X =>"
                                              << std::to_string(this->m_player->getMapX()) << " Y =>" << std::to_string(this->m_player->getMapY()) << std::endl)*/
}

void Map::interact()
{
    int x = this->m_player->getMapX();
    int y = this->m_player->getMapY();

    // get the pos where the player look
    float xDir = m_player->getXLookAt();
    float yDir = m_player->getYLookAt();

    x = xDir;
    y = yDir;

    // check if we interact with an item
    for (auto it = this->m_interactiveObjects.begin(); it != m_interactiveObjects.end();) {
        InteractiveObject* object = *it;
        if (object->getMapX() == x && object->getMapY() == y) {
            bool removable = object->getClicked(this->m_player, this->m_message, &this->m_printMessage);

            if (removable) {
                if (object->getMShadow() != nullptr) {
                    // remove associed shadow
                    for (auto it_sha = m_worldObjects.begin(); it_sha != m_worldObjects.end();) {
                        WorldObject* shadow = *it_sha;
                        if (shadow->getMapX() == x && shadow->getMapY() == y && shadow->getType() == DM_PROJECT_MAP_SHADOW) {
                            m_worldObjects.erase(it_sha);
                            break;
                        }
                        else {
                            ++it_sha;
                        }
                    }
                }
                it = this->m_interactiveObjects.erase(it);
                delete object;
            }
            else{
                ++it;
            }
        }
        else {
            ++it;
        }
    }

    // if player is on the exit go up
    if (this->m_terrain[y * this->getWidth() + x] == DM_PROJECT_MAP_EXIT) {
        this->changeLevel(1);
    }

    // if player is on entrance go down
    if (this->m_terrain[y * this->getWidth() + x] == DM_PROJECT_MAP_ENTRANCE) {
        this->changeLevel(-1);
    }
}

bool Map::canItGoThere(int x, int y)
{
    if (x < 0 || x >= this->getWidth() || y < 0 || y >= this->getHeight()) {
        return false;
    }
    int cell = y * this->getWidth() + x;
    if (this->m_terrain[cell] == DM_PROJECT_MAP_EMPTY || this->m_terrain[cell] == DM_PROJECT_MAP_ENTRANCE || this->m_terrain[cell] == DM_PROJECT_MAP_EXIT) {
        return isDoorOpenAt(x, y);
    }
    return false;
}

bool Map::isDoorOpenAt(int x, int y)
{
    for (auto obj : this->m_interactiveObjects) {
        if((dynamic_cast<const Door*>(obj) == nullptr) )continue;
        Door* door = dynamic_cast<Door*>(obj);
        if (door->getMapX() == x && door->getMapY() == y) {
            if (door->isOpen())
                return true;
            else
                return false;
        }
    }
    return true;
}

bool Map::isDoorOpenAtCell(int cell)
{
    int x = cell % this->getWidth();
    int y = cell / this->getWidth();
    return isDoorOpenAt(x, y);
}
std::string* Map::getStrMessagePtr()
{
    return &(this->m_message);
}
bool* Map::getBoolMessagePtr()
{
    return &this->m_printMessage;
}
bool* Map::getPlayerIsHitPtr()
{
    return &this->m_playerIsHit;
}
bool* Map::getGameFinishedPtr()
{
    return &this->m_gameFinished;
}
