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
    std::vector<Model*> m_listModels;
    TexturesManager     m_texManager;
    ShadersManager*     m_shaderManagerStatic = new ShadersManager("src/shaders/3D_static.vs.glsl", "src/shaders/pointlight.fs.glsl");
    ShadersManager*     m_shaderManagerFacing = new ShadersManager("src/shaders/3D_facing.vs.glsl", "src/shaders/pointlight.fs.glsl");

public:
    ModelsManager();
    ~ModelsManager();
    Model*          getRefModel(const int ID) { return m_listModels[ID]; }
    ShadersManager* getShaderManagerStatic() { return this->m_shaderManagerStatic; };
    ShadersManager* getShaderManagerFacing() { return this->m_shaderManagerFacing; };
};

#endif // PROJET_DM_QUENTIN_LEBON_MODELSMANAGER_HPP
