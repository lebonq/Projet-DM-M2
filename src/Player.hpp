//
// Created by lebonq on 23/12/22.
//

#ifndef PROJET_DM_QUENTIN_LEBON_PLAYER_HPP
#define PROJET_DM_QUENTIN_LEBON_PLAYER_HPP

#include <glimac/FreeflyCamera.hpp>
#include "CombatEntity.hpp"
#include "Model.hpp"
class Player : public CombatEntity {
private:
    int m_gold    = 2345;

    float m_real_x;
    float m_real_z;

    float m_xLookAt;
    float m_yLookAt;

public:
    float getMXLookAt() const;

private:
    int m_PosMapX;
    int m_PosMapY;
    bool m_dead = false;

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
    void changeGold(int amount)
    {
        m_gold += amount;
    };
    int getGold() const
    {
        return m_gold;
    };
    int* getGoldPtr()
    {
        return &m_gold;
    };
    bool* getDeadPtr(){
        return&m_dead;
    };
    void rotateLeftCamera(double angle);
    float getYLookAt() const;
    float getXLookAt() const;
    float getLookAtXValue() const;
    float getLookAtYValue() const;
    void  moveLevel(int map_x, int map_y, float real_x, float real_z, int mapHeight, int mapWidth);
};

#endif // PROJET_DM_QUENTIN_LEBON_PLAYER_HPP
