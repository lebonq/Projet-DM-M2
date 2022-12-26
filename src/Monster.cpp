//
// Created by lebonq on 23/12/22.
//

#include "Monster.hpp"

Monster::Monster(Model* model, glm::mat4 mat,WorldObject* shadow, int map_x, int map_y,int type,int life, int defense, int attack):
    InteractiveObject(model,shadow,mat, map_x, map_y),m_life(life), m_defense(defense), m_attack(attack), m_type(type), m_real_x(map_x), m_real_z(map_y)
{
}

Monster::~Monster()
{
}
void Monster::update()
{
}

void Monster::getClicked(Player* player)
{
    if(this->m_type == DM_PROJECT_MONSTER_SKELETON){
        DEBUG_PRINT("You just it a skeleton damn " << this->m_attack << std::endl);
    }
    player->getRealZ();
}
void Monster::draw()
{
    InteractiveObject::draw();
}

void Monster::draw(Player *player)
{
    float x = player->getRealX();
    float z = player->getRealZ();
    glUniform3fv(this->m_Model->getShaderProgram()->getPlayerPos(),1,glm::value_ptr(glm::vec3(x,0,z)));
    this->draw();
}
