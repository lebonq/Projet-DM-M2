//
// Created by lebonq on 20/12/22.
//

#include "Map.hpp"

Map::Map(const std::string nameLevel)
{
    int width,height;
    std::vector<uint> image_data = Util::readImageFile(nameLevel + ".ppm",&width,&height);
    this->m_width = width;
    this->m_height = height;

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
            break;
        case DM_PROJECT_COLOR_EXIT:
            this->m_terrain.push_back(DM_PROJECT_MAP_EXIT);
            break;
        default:
            PRINT("Bad image for map.");
            exit(-1);
        }
    }

}

Map::~Map()
{

}