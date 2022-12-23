//
// Created by lebonq on 23/12/22.
//

#ifndef PROJET_DM_QUENTIN_LEBON_RENDEREDOBJECT_HPP
#define PROJET_DM_QUENTIN_LEBON_RENDEREDOBJECT_HPP

#include "Model.hpp"
#include "glm/glm.hpp"

class RenderedObject {
private:
    glm::mat4 m_MMatrix;
    Model* m_Model;
    int       m_PosMapX;
    int       m_PosMapY;

public:
    RenderedObject(Model* model,glm::mat4 mat, int map_x, int map_y);
    ~RenderedObject();
    void draw();
};

#endif // PROJET_DM_QUENTIN_LEBON_RENDEREDOBJECT_HPP
