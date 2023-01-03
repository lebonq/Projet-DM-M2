//
// Created by lebonq on 20/12/22.
//

#ifndef PROJET_DM_QUENTIN_LEBON_SHADERSMANAGER_HPP
#define PROJET_DM_QUENTIN_LEBON_SHADERSMANAGER_HPP

#include <glimac/Program.hpp>
#include <vector>
#include "Util.hpp"

class ShadersManager {
private:
    glimac::Program m_shaderProgram;
    // get our uniform vairable fromt the shader
    GLuint m_uMMatrix;
    GLuint m_uVMatrix;
    GLuint m_uPMatrix;
    GLuint m_tex_loc;

    GLuint m_uKd;
    GLuint m_uKs;
    GLuint m_uShininess;
    GLuint m_uRedness;

    GLuint m_uLightPos_vs;
    GLuint m_uLightIntensity;

    GLuint m_playerPos;

public:
    ShadersManager(std::string vs, std::string fs);
    ~ShadersManager();
    void   use() { this->m_shaderProgram.use(); };
    GLuint getMMatrix() const { return m_uMMatrix; }
    GLuint getVMatrix() const { return m_uVMatrix; }
    GLuint getPMatrix() const { return m_uPMatrix; }
    GLuint getTexLoc() const { return m_tex_loc; }
    GLuint getKd() const { return m_uKd; }
    GLuint getKs() const { return m_uKs; }
    GLuint getShininess() const { return m_uShininess; }
    GLuint getLightPosVs() const { return m_uLightPos_vs; }
    GLuint getLightIntensity() const { return m_uLightIntensity; }
    GLuint getPlayerPos() const { return m_playerPos; }
    GLuint getRedness() const { return m_uRedness; }
};

#endif // PROJET_DM_QUENTIN_LEBON_SHADERSMANAGER_HPP
