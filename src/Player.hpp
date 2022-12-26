//
// Created by lebonq on 23/12/22.
//

#ifndef PROJET_DM_QUENTIN_LEBON_PLAYER_HPP
#define PROJET_DM_QUENTIN_LEBON_PLAYER_HPP

#include "Model.hpp"
#include <glimac/FreeflyCamera.hpp>
class Player {
private:
    int m_life    = 100;
    int m_defense = 0;
    int m_attack  = 10;
    int m_gold    = 0;

    float m_real_x;
    float m_real_z;

    int m_PosMapX;
    int m_PosMapY;

    FreeflyCamera* m_camera;

public:
    Player(int map_x, int map_y, float real_x, float real_z,int mapHeight, int mapWidth);
    ~Player();
    void  update();
    float getRealX() const
    {
        return m_real_x;
    };
    float getRealZ() const
    {
        return m_real_z;
    };
    int getMapX() const
    {
        return m_PosMapX;
    };
    int getMapY() const
    {
        return m_PosMapY;
    };
    FreeflyCamera* getCamera() const
    {
        return m_camera;
    };
    void  setRealX(float x)
    {
        m_real_x = x;
        m_PosMapX = static_cast<int>(x)-1;
    };
    void  setRealZ(float z)
    {
        m_real_z = z;
        m_PosMapY = static_cast<int>(z);
    };

    /**
     * This function move the camera thus the player inside the 3D space
     * @param distance
     */
    void moveToLeftCamera(double distance);
    void moveToFrontCamera(double distance);
    /**
     * This function move the player inside the map (discrete space)
     */
    void updateMapPos();
    /**
     * Change the world space coords of the player
     */
    void updateRealPos();
};

#endif // PROJET_DM_QUENTIN_LEBON_PLAYER_HPP
