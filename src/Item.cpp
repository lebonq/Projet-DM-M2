//
// Created by lebonq on 23/12/22.
//

#include "Item.hpp"

Item::Item(Model* model, glm::mat4 mat,WorldObject* shadow, int map_x, int map_y, int id,int amount1, int amount2) :
    InteractiveObject(model,shadow,mat, map_x, map_y), m_ItemType(id), m_ItemValue1(amount1), m_ItemValue2(amount2)
{
}


void Item::getClicked(Player* player)//TO-DO pass player object
{
    if(this->m_ItemType == DM_PROJECT_ITEM_MONEY){
        DEBUG_PRINT("We add gold to the player => gold coins " << std::to_string(this->m_ItemValue1) << std::endl);
        player->changeGold(this->m_ItemValue1);
    }
}
Item::~Item()
{
    DEBUG_PRINT("Item destructor" << std::endl);
    delete this->m_shadow;
    InteractiveObject::~InteractiveObject();
}
