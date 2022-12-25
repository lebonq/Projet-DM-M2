//
// Created by lebonq on 23/12/22.
//

#ifndef PROJET_DM_QUENTIN_LEBON_ITEM_HPP
#define PROJET_DM_QUENTIN_LEBON_ITEM_HPP

#include "InteractiveObject.hpp"
#include "Player.hpp"
class Item : public InteractiveObject {
private:
    int m_ItemType;
    int m_ItemValue1;
    int m_ItemValue2;

public:
    Item(Model* model, glm::mat4 mat, int map_x, int map_y, int id,int amount1, int amount2);
    Item(Model* model, int map_x, int map_y, int id,int amount1, int amount2): Item(model, glm::mat4(1.0f), map_x, map_y, id, amount1, amount2){};
    ~Item();
    void update() override;
    void getClicked() override;
    void draw() override;
    void draw(Player *player);
    //Override draw function


};

#endif // PROJET_DM_QUENTIN_LEBON_ITEM_HPP
