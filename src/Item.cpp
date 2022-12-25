//
// Created by lebonq on 23/12/22.
//

#include "Item.hpp"

Item::Item(Model* model, glm::mat4 mat, int map_x, int map_y, int id,int amount1, int amount2) :
    InteractiveObject(model,mat, map_x, map_y), m_ItemType(id), m_ItemValue1(amount1), m_ItemValue2(amount2)
{
}
void Item::update()
{
    return;
}

void Item::getClicked()//TO-DO pass player object
{
    if(this->m_ItemType == DM_PROJECT_ITEM_GOLD){
        DEBUG_PRINT("We add gold to the player => gold coins " << this->m_ItemValue1 << std::endl);
    }
}
Item::~Item()
{
    InteractiveObject::~InteractiveObject();
}
void Item::draw()
{
    InteractiveObject::draw();
}
void Item::draw(Player *player)
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
