//
// Created by lebonq on 20/12/22.
//

#ifndef PROJET_DM_QUENTIN_LEBON_MAP_HPP
#define PROJET_DM_QUENTIN_LEBON_MAP_HPP

#include <string>
#include <vector>
#include "Data.hpp"
#include "ModelsManager.hpp"
#include "Util.hpp"

class Map {
private:
    int m_width;
    int m_height;
    int m_entrancePos;
    int m_exitPos;
    std::vector<int> m_terrain; //used to store the type of every "chunck" of the map

    ModelsManager m_ModelsManager;

public:
    Map(const std::string& nameLevel);
    void draw();
    ShadersManager& getShadersManager(){return this->m_ModelsManager.getShaderManager();};
    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }
    int getEntrancePos() const { return m_entrancePos; }
    int getExitPos() const { return m_exitPos; }
    ~Map();
};

#endif // PROJET_DM_QUENTIN_LEBON_MAP_HPP
