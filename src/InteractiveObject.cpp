//
// Created by lebonq on 23/12/22.
//

#include "InteractiveObject.hpp"
#include "Player.hpp"
InteractiveObject::InteractiveObject( Model* model, glm::mat4 mat, int map_x, int map_y) :
    RenderedObject(model,mat, map_x, map_y)
{
}
void InteractiveObject::draw()
{
    RenderedObject::draw();
}
