//
// Created by lebonq on 28/12/22.
//

#include "Ladder.hpp"

Ladder::Ladder(int type, Model* model, const glm::mat4& mat, int mapX, int mapY)
    : InteractiveObject(model,nullptr, mat, mapX, mapY) {}

Ladder::~Ladder()
{
}
void Ladder::getClicked(Player* player)
{
}
void Ladder::draw()
{
    InteractiveObject::draw();
}
