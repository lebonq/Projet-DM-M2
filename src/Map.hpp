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
#include "Door.hpp"
#include "Item.hpp"
#include "Ladder.hpp"
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

    bool m_gameFinished = false;
    bool m_playerIsHit = false;

    double m_monsterPreviousTime;

    std::vector<int> m_terrain; //used to store the type of every "chunck" of the map
    std::vector<WorldObject*> m_worldObjects; //owning pointers
    std::vector<InteractiveObject* > m_interactiveObjects;//owning pointers

    Ladder* m_ladder;

    Player* m_player = nullptr;
    json m_data;
    ModelsManager m_ModelsManager;

    //storing message to access it from anywhere
    std::string m_message = "Init";
    bool m_printMessage = false;

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
    void update(double current_time);
    void initInteractiveObject();
    Player* getPlayer() const { return this->m_player; }
    void    interact();
    bool    canItGoThere(int x, int y);
    bool    isDoorOpenAt(int x, int y);
    bool    isDoorOpenAtCell(int cell);
    void    changeLevel(int direction);
    void    startPlayerPosComputation();
    std::string* getStrMessagePtr();
    bool*        getBoolMessagePtr();
    bool* getPlayerIsHitPtr();
    bool* getGameFinishedPtr();
};

#endif // PROJET_DM_QUENTIN_LEBON_MAP_HPP
