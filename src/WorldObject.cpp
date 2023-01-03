//
// Created by lebonq on 23/12/22.
//

#include "WorldObject.hpp"

WorldObject::WorldObject(int type, Model* model, glm::mat4 mat, int map_x, int map_y)
    : RenderedObject(model, mat, map_x, map_y), m_objType(type)
{
}
