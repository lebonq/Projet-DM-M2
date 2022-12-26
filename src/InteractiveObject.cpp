//
// Created by lebonq on 23/12/22.
//

#include "InteractiveObject.hpp"

InteractiveObject::InteractiveObject( Model* model, WorldObject* shadow,glm::mat4 mat, int map_x, int map_y) :
    RenderedObject(model,mat, map_x, map_y), m_shadow(shadow)
{
}
void InteractiveObject::draw()
{
    RenderedObject::draw();
}
