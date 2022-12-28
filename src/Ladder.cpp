//
// Created by lebonq on 28/12/22.
//

#include "Ladder.hpp"

Ladder::Ladder(int type, Model* model, const glm::mat4& mat, int mapX, int mapY)
    : WorldObject(type, model, mat, mapX, mapY) {}

Ladder::~Ladder()
{
}
void Ladder::draw()
{
    RenderedObject::draw();
}
void Ladder::draw(Player *player)
{
    float x = player->getRealX();
    float z = player->getRealZ();
    glUniform3fv(this->m_Model->getShaderProgram()->getPlayerPos(),1,glm::value_ptr(glm::vec3(x,0,z)));
    this->draw();
}

