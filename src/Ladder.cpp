//
// Created by lebonq on 28/12/22.
//

#include "Ladder.hpp"

Ladder::Ladder(int type, Model* model, const glm::mat4& mat, int mapX, int mapY)
    : InteractiveObject(model,nullptr, mat, mapX, mapY) {}

Ladder::~Ladder()
{
    DEBUG_PRINT("Ladder destructor" << std::endl);
    InteractiveObject::~InteractiveObject();
}
bool Ladder::getClicked(Player* player, std::string& message, bool* printMessage)
{;
    return false;
}
void Ladder::draw()
{
    InteractiveObject::draw();
}
