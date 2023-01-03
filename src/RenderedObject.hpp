//
// Created by lebonq on 23/12/22.
//

#ifndef PROJET_DM_QUENTIN_LEBON_RENDEREDOBJECT_HPP
#define PROJET_DM_QUENTIN_LEBON_RENDEREDOBJECT_HPP

#include "Model.hpp"
#include "glm/glm.hpp"

class RenderedObject {
protected:
    glm::mat4 m_MMatrix;
    Model*    m_Model; // non owning pointer
    int       m_PosMapX;
    int       m_PosMapY;

public:
    RenderedObject(Model* model, glm::mat4 mat, int map_x, int map_y);
    virtual ~RenderedObject() = default;
    void updateModelMatrix(const glm::mat4 mat)
    {
        this->m_MMatrix = mat;
    }
    virtual void draw();
    int          getMapX() const
    {
        return m_PosMapX;
    };
    int getMapY() const
    {
        return m_PosMapY;
    };
    void setMapX(int x)
    {
        m_PosMapX = x;
    };
    void setMapY(int y)
    {
        m_PosMapY = y;
    };
};

#endif // PROJET_DM_QUENTIN_LEBON_RENDEREDOBJECT_HPP
