//
// Created by lebonq on 20/12/22.
//

#ifndef PROJET_DM_QUENTIN_LEBON_MODEL_HPP
#define PROJET_DM_QUENTIN_LEBON_MODEL_HPP

#include "Data.hpp"
#include "ShadersManager.hpp"
#include "Util.hpp"
#include "glad/glad.h"
#include "glimac/common.hpp"
#include "vector"

class Model {
private:
    int m_ID;
    std::vector<glimac::ShapeVertex> m_Vertices;
    std::vector<unsigned int> m_ibos;

    GLsizei m_nVertexCount; // Nombre de sommets

    GLuint m_textureId;
    ShadersManager& m_shaderProgram; //Not owning pointer

    glm::vec3 m_kd;
    glm::vec3 m_ks;
    GLfloat m_shininess;

    GLuint m_vbo;
    GLuint m_vao;
    GLuint m_ibo;
public:
    Model(const int ID, const GLuint texID, ShadersManager& mShaderProgram);
    ~Model();
    void draw(const glm::mat4& mmatrix);
    void bindModel();
    void unBindModel();
    const glimac::ShapeVertex* getDataPointer() const;
};

#endif // PROJET_DM_QUENTIN_LEBON_MODEL_HPP
