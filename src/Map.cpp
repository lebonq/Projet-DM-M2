//
// Created by lebonq on 20/12/22.
//

#include "Map.hpp"

Map::Map(const std::string& nameLevel)
{
    DEBUG_PRINT("Create a Map " << std::endl);
    int               width, height;
    std::vector<uint> image_data = Util::readImageFile(nameLevel + ".ppm", &width, &height);
    this->m_width                = width;
    this->m_height               = height;

    int cpt = 0;
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
}

void Map::draw()
{
    int index_right = 0;
    int index_bot   = 0;
    int index       = 0;

    Model* wall = this->m_ModelsManager.getRefModel(DM_PROJECT_ID_MANAGER_WALL);
    wall->bindModel();
    wall->resetPos();
    wall->translate(glm::vec3(0, 0.5, 0.5));
    for (int y = 0; y < this->m_height; y++) {
        for (int x = 0; x < this->m_width; x++) {
            index       = y * this->m_width + x;
            index_right = index + 1;
            index_bot   = index + this->m_width;

            wall->translate(glm::vec3(1, 0, 0));

            // For real wall facing X
            if (this->m_terrain[index_bot] != DM_PROJECT_MAP_WALL && this->m_terrain[index] == DM_PROJECT_MAP_WALL)
                wall->draw();
            // || index_bot >= this->m_width*this->m_height  is for when we touch the border of the map to make sure we draw our wall
            //Si index n'est pas un mur et que index_bot est un mur ou hors du tableau alors on draw
            if (this->m_terrain[index] != DM_PROJECT_MAP_WALL && (this->m_terrain[index_bot] == DM_PROJECT_MAP_WALL||  y+1 >= this->m_height) ) {
                wall->rotate(180, glm::vec3(0, 1, 0)); // Those rotation allow us to orient the wall inside the room
                wall->draw();
                wall->rotate(-180, glm::vec3(0, 1, 0));
            }

            // For wall bewteen water and floor
            wall->translate(glm::vec3(0, -1, 0));
            if (this->m_terrain[index] != DM_PROJECT_MAP_WATER && this->m_terrain[index_bot] == DM_PROJECT_MAP_WATER )
                wall->draw();
            if ((this->m_terrain[index_bot] != DM_PROJECT_MAP_WATER || y+1 >= this->m_height) && this->m_terrain[index] == DM_PROJECT_MAP_WATER) {
                wall->rotate(180, glm::vec3(0, 1, 0)); // Those rotation allow us to orient the wall inside the room
                wall->draw();
                wall->rotate(-180, glm::vec3(0, 1, 0));
            }
            wall->translate(glm::vec3(0, 1, 0));

            //Wall touching the top
            if (y == 0 && this->m_terrain[index] != DM_PROJECT_MAP_WALL) {
                wall->translate(glm::vec3(0, 0, -1));
                wall->draw();
                if (this->m_terrain[index] == DM_PROJECT_MAP_WATER) {
                    wall->translate(glm::vec3(0, -1, 0));
                    wall->draw();
                    wall->translate(glm::vec3(0, 1, 0));
                }
                wall->translate(glm::vec3(0, 0, 1));
            }

            // Wall facing Z
            wall->rotate(90, glm::vec3(0, 1, 0));
            wall->translate(glm::vec3(0.5, 0, 0.5));
            //x -(y*width)
            if (this->m_terrain[index_right] != DM_PROJECT_MAP_WALL && this->m_terrain[index] == DM_PROJECT_MAP_WALL)
                wall->draw();
            //|| x+1 >= this->m_width) To check is we are  on the right side of the maze
            if (this->m_terrain[index] != DM_PROJECT_MAP_WALL && (this->m_terrain[index_right] == DM_PROJECT_MAP_WALL || x+1 >= this->m_width)) {
                wall->rotate(180, glm::vec3(0, 1, 0));
                wall->draw();
                wall->rotate(-180, glm::vec3(0, 1, 0));
            }

            if (x == 0 && this->m_terrain[index] != DM_PROJECT_MAP_WALL) {
                wall->translate(glm::vec3(0, 0, -1));
                wall->draw();
                if (this->m_terrain[index] == DM_PROJECT_MAP_WATER) {
                    wall->translate(glm::vec3(0, -1, 0));
                    wall->draw();
                    wall->translate(glm::vec3(0, 1, 0));
                }
                wall->translate(glm::vec3(0, 0, 1));
            }

            // Florr to water
            wall->translate(glm::vec3(0, -1, 0));
            if (this->m_terrain[index] != DM_PROJECT_MAP_WATER && this->m_terrain[index_right] == DM_PROJECT_MAP_WATER)
                wall->draw();
            if ((this->m_terrain[index_right] != DM_PROJECT_MAP_WATER || x+1 >= this->m_width) && this->m_terrain[index] == DM_PROJECT_MAP_WATER) {
                wall->rotate(180, glm::vec3(0, 1, 0)); // Those rotation allow us to orient the wall inside the room
                wall->draw();
                wall->rotate(-180, glm::vec3(0, 1, 0));
            }
            wall->translate(glm::vec3(0, 1, 0));

            wall->translate(glm::vec3(-0.5, 0, -0.5));
            wall->rotate(-90, glm::vec3(0, 1, 0));
        }
        wall->translate(glm::vec3(-this->m_width, 0, 1));
    }
    wall->unBindModel();

    // draw floor
    Model* floor = this->m_ModelsManager.getRefModel(DM_PROJECT_ID_MANAGER_FLOOR);
    floor->bindModel();
    floor->resetPos();
    for (int y = 0; y < this->m_height; y++) {
        for (int x = 0; x < this->m_width; x++) {
            index = y * this->m_width + x;
            floor->translate(glm::vec3(1, 0, 0));
            if (this->m_terrain[index] == DM_PROJECT_MAP_EMPTY ||
                this->m_terrain[index] == DM_PROJECT_MAP_ENTRANCE ||
                this->m_terrain[index] == DM_PROJECT_MAP_EXIT ||
                this->m_terrain[index] == DM_PROJECT_MAP_WATER) {
                if (this->m_terrain[index] != DM_PROJECT_MAP_WATER)
                    floor->draw();
                floor->translate(glm::vec3(0, 1, 0));
                floor->rotate(180, glm::vec3(1, 0, 0)); // Make the floor face downward
                floor->draw();
                floor->rotate(-180, glm::vec3(1, 0, 0));
                floor->translate(glm::vec3(0, -1, 0));
            }
        }
        floor->translate(glm::vec3(-this->m_width, 0, 1));
    }
    floor->unBindModel();

    // Draw Water
    Model* water = this->m_ModelsManager.getRefModel(DM_PROJECT_ID_MANAGER_WATER);
    water->bindModel();
    water->resetPos();
    water->translate(glm::vec3(0, -0.25, 0));
    for (int y = 0; y < this->m_height; y++) {
        for (int x = 0; x < this->m_width; x++) {
            index = y * this->m_width + x;
            water->translate(glm::vec3(1, 0, 0));
            if (this->m_terrain[index] == DM_PROJECT_MAP_WATER) {
                water->draw();
            }
        }
        water->translate(glm::vec3(-this->m_width, 0, 1));
    }
    water->unBindModel();
}
