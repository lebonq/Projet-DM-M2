//
// Created by lebonq on 20/12/22.
//

#include "ModelsManager.hpp"
ModelsManager::ModelsManager()
{
    glimac::ShapeVertex quadVertices[] = {
             glimac::ShapeVertex{glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 0.0f)},  // bottom left
             glimac::ShapeVertex{glm::vec3( 0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 0.0f)},  // bottom right
             glimac::ShapeVertex{glm::vec3( 0.5f,  0.5f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 1.0f)},  // top right
             glimac::ShapeVertex{glm::vec3(-0.5f,  0.5f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 1.0f)}   // top left
    };

    // Index data for a quad
    std::vector<unsigned int> quadIndices = {
        0, 1, 2,  // first triangle
        2, 3, 0   // second triangle
    };

    Model wall(quadVertices,quadIndices,4,this->m_texManager.getTexId(DM_PROJECT_ID_MANAGER_WALL));
    this->m_listModels.push_back(wall);
}
ModelsManager::~ModelsManager()
{
}
