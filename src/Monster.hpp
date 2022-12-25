//
// Created by lebonq on 23/12/22.
//

#ifndef PROJET_DM_QUENTIN_LEBON_MONSTER_HPP
#define PROJET_DM_QUENTIN_LEBON_MONSTER_HPP

#include "InteractiveObject.hpp"
#include "Player.hpp"
class Monster : public InteractiveObject {
private:
    int m_life;
    int m_defense;
    int m_attack ;
    int m_type;

    float m_real_x = 0;
    float m_real_z = 0;
public:
    Monster(Model* model, glm::mat4 mat, int map_x, int map_y,int type,int life, int defense, int attack);
    ~Monster();
    void  update() override;
    void  getClicked() override;
    void  draw() override;
        void draw(Player *player);//put a new class for this
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
    };
    void  setRealZ(float z)
    {
        m_real_z = z;
    };
};

#endif // PROJET_DM_QUENTIN_LEBON_MONSTER_HPP
