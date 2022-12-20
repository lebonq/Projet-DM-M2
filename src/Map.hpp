//
// Created by lebonq on 20/12/22.
//

#ifndef PROJET_DM_QUENTIN_LEBON_MAP_HPP
#define PROJET_DM_QUENTIN_LEBON_MAP_HPP

#include <string>
#include <vector>
#include "Util.hpp"
#include "Data.hpp"

class Map {
private:
    int m_width;
    int m_height;
    std::vector<int> m_terrain; //used to store the type of every "chunck" of the map

public:
    Map(const std::string nameLevel);
    ~Map();
};

#endif // PROJET_DM_QUENTIN_LEBON_MAP_HPP
