//
// Created by lebonq on 23/12/22.
//

#include "RenderedObject.hpp"

RenderedObject::RenderedObject(Model* model,glm::mat4 mat, int map_x, int map_y)
    : m_MMatrix(mat), m_Model(model), m_PosMapX(map_x), m_PosMapY(map_y)
{
}

/**
 * @warning Don't forget to bind the model before drawing !
 */
void RenderedObject::draw()
{
    this->m_Model->bindModel();
    this->m_Model->draw(this->m_MMatrix);
    this->m_Model->unBindModel();

}
