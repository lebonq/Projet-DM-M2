//
// Created by lebonq on 23/12/22.
//

#ifndef PROJET_DM_QUENTIN_LEBON_WORLDOBJECT_HPP
#define PROJET_DM_QUENTIN_LEBON_WORLDOBJECT_HPP

#include "RenderedObject.hpp"

class WorldObject : public RenderedObject {
private:
    int m_objType;

public:
    WorldObject(int type, Model* model, glm::mat4 mat, int map_x, int map_y);
    ~WorldObject(){};
    int getType() { return m_objType; }
};

#endif // PROJET_DM_QUENTIN_LEBON_WORLDOBJECT_HPP
