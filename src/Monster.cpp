//
// Created by lebonq on 23/12/22.
//

#include "Monster.hpp"

Monster::Monster(Model* model, glm::mat4 mat, int map_x, int map_y,int type,int life, int defense, int attack):
    InteractiveObject(model,mat, map_x, map_y),m_life(life), m_defense(defense), m_attack(attack), m_type(type), m_real_x(map_x), m_real_z(map_y)
{
}

Monster::~Monster()
{
}
void Monster::update()
{
}

void Monster::getClicked()
{
}
void Monster::draw()
{
    InteractiveObject::draw();
}

void Monster::draw(Player *player)
{
    float x = player->getRealX();
    float z = player->getRealZ();

    glm::mat4 mat = glm::mat4(1.0f);
    glm::vec3 to_player(x - static_cast<float>(this->m_PosMapX+1), z - static_cast<float>(this->m_PosMapY),0.0f);
    glm::vec3 to_one(0.0f, static_cast<float>(this->m_PosMapY+1) - static_cast<float>(this->m_PosMapY)  ,0.0f);
    float angle = Util::calcAngle(to_player,to_one);
    //to orient angle
    if(x < static_cast<float>(this->m_PosMapX+1)){
        angle = -angle;
    }

    mat = glm::translate(mat,glm::vec3(this->m_PosMapX+1, 0.40, this->m_PosMapY));
    mat = glm::rotate(mat, angle, glm::vec3(0.0f, 1.0f, 0.0f));
    this->m_MMatrix = mat;
    this->draw();
}
