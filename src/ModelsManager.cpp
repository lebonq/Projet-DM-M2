//
// Created by lebonq on 20/12/22.
//

#include "ModelsManager.hpp"
ModelsManager::ModelsManager()
{
    DEBUG_PRINT("Build ModelsManager " << std::endl);
    DEBUG_PRINT("Load Wall Model " << std::endl);
    Model* wall = new Model(DM_PROJECT_ID_MANAGER_WALL, this->m_texManager.getTexId(DM_PROJECT_ID_MANAGER_WALL), this->m_shaderManager);
    this->m_listModels.push_back(wall);
    DEBUG_PRINT("Load Floor Model " << std::endl);
    Model* floor = new Model(DM_PROJECT_ID_MANAGER_FLOOR, this->m_texManager.getTexId(DM_PROJECT_ID_MANAGER_FLOOR), this->m_shaderManager);
    this->m_listModels.push_back(floor);
    DEBUG_PRINT("Load Water Model " << std::endl);
    Model* water = new Model(DM_PROJECT_ID_MANAGER_WATER, this->m_texManager.getTexId(DM_PROJECT_ID_MANAGER_WATER), this->m_shaderManager);
    this->m_listModels.push_back(water);
}
ModelsManager::~ModelsManager()
{
    DEBUG_PRINT("Delete ModelsManager " << std::endl);
    for (auto model :this->m_listModels) {
        delete model;
    }
}
