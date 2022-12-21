//
// Created by lebonq on 20/12/22.
//

#include "ModelsManager.hpp"
ModelsManager::ModelsManager()
{
    DEBUG_PRINT("Build ModelsManager " << std::endl);
    DEBUG_PRINT("Load Wall Model " << std::endl);
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

    Model* wall = new Model(quadVertices, quadIndices, 4, this->m_texManager.getTexId(DM_PROJECT_ID_MANAGER_WALL), this->m_shaderManager);
    this->m_listModels.push_back(wall);
    DEBUG_PRINT("Load Floor Model " << std::endl);
}
ModelsManager::~ModelsManager()
{
    DEBUG_PRINT("Delete ModelsManager " << std::endl);
    for (auto model :this->m_listModels) {
        delete model;
    }
}
