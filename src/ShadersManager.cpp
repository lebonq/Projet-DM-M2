//
// Created by lebonq on 20/12/22.
//

#include "ShadersManager.hpp"
ShadersManager::ShadersManager()
{
    this->m_shaderProgram = glimac::loadProgram("src/shaders/sphere3D.vs.glsl","src/shaders/pointlight.fs.glsl");
    //get our uniform vairable fromt the shader
    this->m_uMMatrix = glGetUniformLocation(this->m_shaderProgram.getGLId(),"uMMatrix");
    this->m_uVMatrix = glGetUniformLocation(this->m_shaderProgram.getGLId(),"uVMatrix");
    this->m_uPMatrix = glGetUniformLocation(this->m_shaderProgram.getGLId(),"uPMatrix");
    this->m_tex_loc = glGetUniformLocation(this->m_shaderProgram.getGLId(),"uTex_data");

    this->m_uKd = glGetUniformLocation(this->m_shaderProgram.getGLId(),"uKd");
    this->m_uKs = glGetUniformLocation(this->m_shaderProgram.getGLId(),"uKs");
    this->m_uShininess = glGetUniformLocation(this->m_shaderProgram.getGLId(),"uShininess");

    this->m_uLightPos_vs = glGetUniformLocation(this->m_shaderProgram.getGLId(),"uLightPos_vs");
    this->m_uLightIntensity = glGetUniformLocation(this->m_shaderProgram.getGLId(),"uLightIntensity");
}
ShadersManager::~ShadersManager()
{
}
