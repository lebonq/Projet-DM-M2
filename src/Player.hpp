//
// Created by lebonq on 23/12/22.
//

#ifndef PROJET_DM_QUENTIN_LEBON_PLAYER_HPP
#define PROJET_DM_QUENTIN_LEBON_PLAYER_HPP

#include "InteractiveObject.hpp"
class Player : public InteractiveObject {
private:
    int m_life    = 100;
    int m_defense = 0;
    int m_attack  = 10;

    float m_real_x = 0;
    float m_real_z = 0;

public:
    Player(Model* model, glm::mat4 mat, int map_x, int map_y, float real_x, float real_z);
    ~Player();
    void  update() override;
    void  getClicked() override;
    void  draw() override;
    float getRealX() const
    {
        return m_real_x;
    };
    float getRealZ() const
    {
        return m_real_z;
    };
    void  setRealX(float x)
    {
        m_real_x = x;
        m_PosMapX = x;
    };
    void  setRealZ(float z)
    {
        m_real_z = z;
        m_PosMapY = z;
    };

};

#endif // PROJET_DM_QUENTIN_LEBON_PLAYER_HPP
