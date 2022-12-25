//
// Created by lebonq on 20/12/22.
//

#include "Map.hpp"

Map::Map(const std::string& nameLevel)
{
    DEBUG_PRINT("Create a Map " << std::endl);
    std::ifstream json_file(nameLevel + ".json");
    this->m_data = json::parse(json_file);

    this->m_nLevels = this->m_data["levels"].size();
    this->m_currentLevel = 0;
    this->loadMap(this->m_data["levels"]["0"]["image"]);

    DEBUG_PRINT(this->m_data["levels"].size() << std::endl);
    this->initWorldObject();
    this->initInteractiveObject();

    //set starting pos player
    int pos_player= this->getEntrancePos();
    int cam_x = pos_player%this->getWidth();
    int cam_z = (pos_player-cam_x)/this->getWidth();

    this->m_player = new Player(nullptr, glm::mat4(1.0f), cam_x, cam_z, cam_x+1, cam_z);
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
    delete this->m_player;

}

void Map::initWorldObject()
{
    int index_right = 0;
    int index_bot   = 0;
    int index       = 0;

    this->m_worldObjects.clear();

    Model* wall = this->m_ModelsManager.getRefModel(DM_PROJECT_ID_MANAGER_WALL);
    glm::mat4 wallMatrix(1);
    glm::mat4 floorMatrix(1);
    glm::mat4 waterMatrix(1);

    wallMatrix = glm::translate(wallMatrix,glm::vec3(0, 0.5, 0.5));
    for (int y = 0; y < this->m_height; y++) {
        for (int x = 0; x < this->m_width; x++) {
            index       = y * this->m_width + x;
            index_right = index + 1;
            index_bot   = index + this->m_width;

            wallMatrix = glm::translate(wallMatrix,glm::vec3(1, 0, 0));

            // For real wall facing X
            if (this->m_terrain[index_bot] != DM_PROJECT_MAP_WALL && this->m_terrain[index] == DM_PROJECT_MAP_WALL)
                this->m_worldObjects.push_back(new WorldObject(DM_PROJECT_MAP_WALL,wall,wallMatrix,x,y));
            // || index_bot >= this->m_width*this->m_height  is for when we touch the border of the map to make sure we draw our wall
            // Si index n'est pas un mur et que index_bot est un mur ou hors du tableau alors on draw
            if (this->m_terrain[index] != DM_PROJECT_MAP_WALL && (this->m_terrain[index_bot] == DM_PROJECT_MAP_WALL || y + 1 >= this->m_height)) {
                wallMatrix = glm::rotate(wallMatrix,glm::radians(180.0f), glm::vec3(0, 1, 0)); // Those rotation allow us to orient the wall inside the room
                this->m_worldObjects.push_back(new WorldObject(DM_PROJECT_MAP_WALL,wall,wallMatrix,x,y));
                wallMatrix = glm::rotate(wallMatrix,glm::radians(-180.0f), glm::vec3(0, 1, 0));
            }

            // For wall bewteen water and floor
            wallMatrix = glm::translate(wallMatrix,glm::vec3(0, -1, 0));
            if (this->m_terrain[index] != DM_PROJECT_MAP_WATER && this->m_terrain[index_bot] == DM_PROJECT_MAP_WATER)
                this->m_worldObjects.push_back(new WorldObject(DM_PROJECT_MAP_WALL,wall,wallMatrix,x,y));
            if ((this->m_terrain[index_bot] != DM_PROJECT_MAP_WATER || y + 1 >= this->m_height) && this->m_terrain[index] == DM_PROJECT_MAP_WATER) {
                wallMatrix = glm::rotate(wallMatrix,glm::radians(180.0f), glm::vec3(0, 1, 0)); // Those rotation allow us to orient the wall inside the room
                this->m_worldObjects.push_back(new WorldObject(DM_PROJECT_MAP_WALL,wall,wallMatrix,x,y));
                wallMatrix = glm::rotate(wallMatrix,glm::radians(-180.0f), glm::vec3(0, 1, 0));
            }
            wallMatrix = glm::translate(wallMatrix,glm::vec3(0, 1, 0));

            // Wall touching the top
            if (y == 0 && this->m_terrain[index] != DM_PROJECT_MAP_WALL) {
                wallMatrix = glm::translate(wallMatrix,glm::vec3(0, 0, -1));
                this->m_worldObjects.push_back(new WorldObject(DM_PROJECT_MAP_WALL,wall,wallMatrix,x,y));
                if (this->m_terrain[index] == DM_PROJECT_MAP_WATER) {
                    wallMatrix = glm::translate(wallMatrix,glm::vec3(0, -1, 0));
                    this->m_worldObjects.push_back(new WorldObject(DM_PROJECT_MAP_WALL,wall,wallMatrix,x,y));
                    wallMatrix = glm::translate(wallMatrix,glm::vec3(0, 1, 0));
                }
                wallMatrix = glm::translate(wallMatrix,glm::vec3(0, 0, 1));
            }

            // Wall facing Z
            wallMatrix = glm::rotate(wallMatrix,glm::radians(90.0f), glm::vec3(0, 1, 0));
            wallMatrix = glm::translate(wallMatrix,glm::vec3(0.5, 0, 0.5));
            // x -(y*width)
            if (this->m_terrain[index_right] != DM_PROJECT_MAP_WALL && this->m_terrain[index] == DM_PROJECT_MAP_WALL)
                this->m_worldObjects.push_back(new WorldObject(DM_PROJECT_MAP_WALL,wall,wallMatrix,x,y));
            //|| x+1 >= this->m_width) To check is we are  on the right side of the maze
            if (this->m_terrain[index] != DM_PROJECT_MAP_WALL && (this->m_terrain[index_right] == DM_PROJECT_MAP_WALL || x + 1 >= this->m_width)) {
                wallMatrix = glm::rotate(wallMatrix,glm::radians(180.0f), glm::vec3(0, 1, 0));
                this->m_worldObjects.push_back(new WorldObject(DM_PROJECT_MAP_WALL,wall,wallMatrix,x,y));
                wallMatrix = glm::rotate(wallMatrix,glm::radians(-180.0f), glm::vec3(0, 1, 0));
            }

            if (x == 0 && this->m_terrain[index] != DM_PROJECT_MAP_WALL) {
                wallMatrix = glm::translate(wallMatrix,glm::vec3(0, 0, -1));
                this->m_worldObjects.push_back(new WorldObject(DM_PROJECT_MAP_WALL,wall,wallMatrix,x,y));
                if (this->m_terrain[index] == DM_PROJECT_MAP_WATER) {
                    wallMatrix = glm::translate(wallMatrix,glm::vec3(0, -1, 0));
                    this->m_worldObjects.push_back(new WorldObject(DM_PROJECT_MAP_WALL,wall,wallMatrix,x,y));
                    wallMatrix = glm::translate(wallMatrix,glm::vec3(0, 1, 0));
                }
                wallMatrix = glm::translate(wallMatrix,glm::vec3(0, 0, 1));
            }

            // Florr to water
            wallMatrix = glm::translate(wallMatrix,glm::vec3(0, -1, 0));
            if (this->m_terrain[index] != DM_PROJECT_MAP_WATER && this->m_terrain[index_right] == DM_PROJECT_MAP_WATER)
                this->m_worldObjects.push_back(new WorldObject(DM_PROJECT_MAP_WALL,wall,wallMatrix,x,y));
            if ((this->m_terrain[index_right] != DM_PROJECT_MAP_WATER || x + 1 >= this->m_width) && this->m_terrain[index] == DM_PROJECT_MAP_WATER) {
                wallMatrix = glm::rotate(wallMatrix,glm::radians(180.0f), glm::vec3(0, 1, 0)); // Those rotation allow us to orient the wall inside the room
                this->m_worldObjects.push_back(new WorldObject(DM_PROJECT_MAP_WALL,wall,wallMatrix,x,y));
                wallMatrix = glm::rotate(wallMatrix,glm::radians(-180.0f), glm::vec3(0, 1, 0));
            }
            wallMatrix = glm::translate(wallMatrix,glm::vec3(0, 1, 0));

            wallMatrix = glm::translate(wallMatrix,glm::vec3(-0.5, 0, -0.5));
            wallMatrix = glm::rotate(wallMatrix,glm::radians(-90.0f), glm::vec3(0, 1, 0));
        }
        wallMatrix = glm::translate(wallMatrix,glm::vec3(-this->m_width, 0, 1));
    }

    // draw floor
    Model* floor = this->m_ModelsManager.getRefModel(DM_PROJECT_ID_MANAGER_FLOOR);


    for (int y = 0; y < this->m_height; y++) {
        for (int x = 0; x < this->m_width; x++) {
            index = y * this->m_width + x;
            floorMatrix = glm::translate(floorMatrix,glm::vec3(1, 0, 0));
            if (this->m_terrain[index] == DM_PROJECT_MAP_EMPTY ||
                this->m_terrain[index] == DM_PROJECT_MAP_ENTRANCE ||
                this->m_terrain[index] == DM_PROJECT_MAP_EXIT ||
                this->m_terrain[index] == DM_PROJECT_MAP_WATER) {
                if (this->m_terrain[index] != DM_PROJECT_MAP_WATER)
                    this->m_worldObjects.push_back(new WorldObject(DM_PROJECT_MAP_EMPTY,floor,floorMatrix,x,y));
                floorMatrix = glm::translate(floorMatrix,glm::vec3(0, 1, 0));
                floorMatrix = glm::rotate(floorMatrix,glm::radians(180.0f), glm::vec3(1, 0, 0)); // Make the floor face downward
                this->m_worldObjects.push_back(new WorldObject(DM_PROJECT_MAP_EMPTY,floor,floorMatrix,x,y));
                floorMatrix = glm::rotate(floorMatrix,glm::radians(-180.0f), glm::vec3(1, 0, 0));
                floorMatrix = glm::translate(floorMatrix,glm::vec3(0, -1, 0));
            }
        }
        floorMatrix = glm::translate(floorMatrix,glm::vec3(-this->m_width, 0, 1));
    }
    floor->unBindModel();

    // Draw Water
    Model* water = this->m_ModelsManager.getRefModel(DM_PROJECT_ID_MANAGER_WATER);

    waterMatrix = glm::translate(waterMatrix,glm::vec3(0, -0.25, 0));
    for (int y = 0; y < this->m_height; y++) {
        for (int x = 0; x < this->m_width; x++) {
            index = y * this->m_width + x;
            waterMatrix = glm::translate(waterMatrix,glm::vec3(1, 0, 0));
            if (this->m_terrain[index] == DM_PROJECT_MAP_WATER) {
                this->m_worldObjects.push_back(new WorldObject(DM_PROJECT_MAP_WATER,water,waterMatrix,x,y));
            }
        }
        waterMatrix = glm::translate(waterMatrix,glm::vec3(-this->m_width, 0, 1));
    }

}

void Map::initInteractiveObject(){
    this->m_worldItems.clear();
    json listItems = this->m_data["levels"][std::to_string(this->m_currentLevel)]["items"];
    Model* shadow = this->m_ModelsManager.getRefModel(DM_PROJECT_ID_MANAGER_SHADOW);
    for(auto item : listItems){
        Model* item_model = this->m_ModelsManager.getRefModel(item["id_model"]);
        int x = item["pos_x"];
        int y = item["pos_y"];
        glm::mat4 mmatrix(1.0f);
        mmatrix = glm::translate(mmatrix,glm::vec3(x+1, 0.40, y));
        glm::mat4 smatrix(1.0f);
        smatrix = glm::translate(smatrix,glm::vec3(x+1, 0.01f, y));
        this->m_worldObjects.push_back(new WorldObject(DM_PROJECT_MAP_SHADOW,shadow,smatrix,x,y));
        Item* item_ptr = new Item(item_model,mmatrix,x,y,item["type"],item["amount_0"],item["amount_1"]);
        this->m_worldItems.push_back(item_ptr);
        DEBUG_PRINT("Item type : " << item["type"] << " x : " << item["pos_x"] << " y : " << item["pos_y"] << std::endl);
    }
}

void Map::draw()
{
    for (WorldObject* object : this->m_worldObjects) {
        object->draw();
    }
    for (Item* item : this->m_worldItems) {
        item->draw(this->m_player);
    }
}
void Map::update()
{

}
