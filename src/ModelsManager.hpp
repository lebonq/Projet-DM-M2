//
// Created by lebonq on 20/12/22.
//

#ifndef PROJET_DM_QUENTIN_LEBON_MODELSMANAGER_HPP
#define PROJET_DM_QUENTIN_LEBON_MODELSMANAGER_HPP

#include <vector>
#include "Model.hpp"
#include "ShadersManager.hpp"
#include "TexturesManager.hpp"

class ModelsManager {
private:
    std::vector<Model> m_listModels;
    TexturesManager m_texManager;
    ShadersManager m_shaderManager;
public:
    ModelsManager();
    ~ModelsManager();
    Model& getRefModel(const int ID){return m_listModels[ID];}
};

#endif // PROJET_DM_QUENTIN_LEBON_MODELSMANAGER_HPP
