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
    Model m_Model;
    int m_pos_map_x;
    int m_pos_map_y;
    float m_pos_real_x;
    float m_pos_real_y;

public:
   virtual double GetBalance();   // Obtain balance.
   virtual void PrintBalance() = 0;   // Pure virtual function.
};

#endif // PROJET_DM_QUENTIN_LEBON_RENDEREDOBJECT_HPP
