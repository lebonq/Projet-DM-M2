//
// Created by lebonq on 23/12/22.
//

#include "InteractiveObject.hpp"

InteractiveObject::InteractiveObject( Model* model, WorldObject* shadow,glm::mat4 mat, int map_x, int map_y) :
    RenderedObject(model,mat, map_x, map_y), m_shadow(shadow)
{
}
void InteractiveObject::draw(Player(*player))
{
    float x = player->getRealX();
    float z = player->getRealZ();
    glUniform3fv(this->m_Model->getShaderProgram()->getPlayerPos(),1,glm::value_ptr(glm::vec3(x,0,z)));
    RenderedObject::draw();
}
void InteractiveObject::draw()
{
    RenderedObject::draw();
}
WorldObject* InteractiveObject::getMShadow() const
{
    return m_shadow;
}
