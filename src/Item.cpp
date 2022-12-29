//
// Created by lebonq on 23/12/22.
//

#include "Item.hpp"

Item::Item(Model* model, glm::mat4 mat,WorldObject* shadow, int map_x, int map_y, int id,int amount1, int amount2) :
    InteractiveObject(model,shadow,mat, map_x, map_y), m_ItemType(id), m_ItemValue1(amount1), m_ItemValue2(amount2)
{
}


bool Item::getClicked(Player* player)//TO-DO pass player object
{
    if(this->m_ItemType == DM_PROJECT_ITEM_MONEY){
        DEBUG_PRINT("We add gold to the player => gold coins " << std::to_string(this->m_ItemValue1) << std::endl);
        player->changeGold(this->m_ItemValue1);
    }
    else if(this->m_ItemType == DM_PROJECT_ITEM_LIVE){
        DEBUG_PRINT("We add life to the player => life points " << std::to_string(this->m_ItemValue1) << std::endl);
        player->changeLife(this->m_ItemValue1);
    }
    else if(this->m_ItemType == DM_PROJECT_ITEM_DEFENSE){
        DEBUG_PRINT("We add defense to the player => defense points " << std::to_string(this->m_ItemValue1) << std::endl);
        player->changeDefense(this->m_ItemValue1);
    }
    else if(this->m_ItemType == DM_PROJECT_ITEM_ATTACK){
        DEBUG_PRINT("We add attack to the player => attack points " << std::to_string(this->m_ItemValue1) << std::endl);
        player->changeAttack(this->m_ItemValue1);
    }
    else if(this->m_ItemType == DM_PROJECT_ITEM_DEFENSE_AND_ATTACK){
        DEBUG_PRINT("We add attack and defense to the player =>  attack and defense points " << std::to_string(this->m_ItemValue1) << std::endl);
        player->changeAttack(this->m_ItemValue1);
        player->changeDefense(this->m_ItemValue2);
    }
    else{
        DEBUG_PRINT("We add nothing to the player =>  Item unknown type" << std::endl);
    }
    return true;
}
Item::~Item()
{
    DEBUG_PRINT("Item destructor" << std::endl);
    InteractiveObject::~InteractiveObject();
}
