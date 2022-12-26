//
// Created by lebonq on 20/12/22.
//

#ifndef PROJET_DM_QUENTIN_LEBON_MAP_HPP
#define PROJET_DM_QUENTIN_LEBON_MAP_HPP

#include <fstream>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>
#include "Data.hpp"
#include "Item.hpp"
#include "ModelsManager.hpp"
#include "Monster.hpp"
#include "Player.hpp"
#include "Util.hpp"
#include "WorldObject.hpp"

using json = nlohmann::json;

class Map {
private:
    int m_width;
    int m_height;
    int m_entrancePos;
    int m_exitPos;
    int m_nLevels;
    int m_currentLevel;

    std::vector<int> m_terrain; //used to store the type of every "chunck" of the map
    std::vector<WorldObject*> m_worldObjects; //owning pointers
    std::vector<Item*> m_worldItems; //owning pointers
    std::vector<Monster*> m_worldMonsters; //owning pointers
    Player* m_player;
    json m_data;
    ModelsManager m_ModelsManager;

public:
    Map(const std::string& nameLevel);
    void initWorldObject();
    void drawStatic();
    void drawFacing();
    ShadersManager* getShadersManagerFacing(){return this->m_ModelsManager.getShaderManagerFacing();};
    ShadersManager* getShadersManagerStatic(){return this->m_ModelsManager.getShaderManagerStatic();};
    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }
    int getEntrancePos() const { return m_entrancePos; }
    int getExitPos() const { return m_exitPos; }
    ~Map();
    void loadMap(const std::string& nameLevel);
    void update();
    void initInteractiveObject();
    Player* getPlayer() const { return this->m_player; }
};

#endif // PROJET_DM_QUENTIN_LEBON_MAP_HPP
