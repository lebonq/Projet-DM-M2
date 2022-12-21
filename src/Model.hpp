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
    glimac::ShapeVertex* m_Vertices;
    std::vector<unsigned int> m_ibos;

    GLsizei m_nVertexCount; // Nombre de sommets

    int m_textureId;
    ShadersManager& m_shaderProgram; //Not owning pointer

    glm::vec3 m_kd = glm::vec3(2,2,2);
    glm::vec3 m_ks = glm::vec3(0,0,0);
    GLfloat m_shininess = 2.0f;

    glm::mat4 m_MMatrix;

    GLuint m_vbo;
    GLuint m_vao;
    GLuint m_ibo;
public:
    Model(glimac::ShapeVertex* vertices, const std::vector<unsigned int> ibo, const int nb_vertices, const GLuint texID, ShadersManager& mShaderProgram);
    ~Model();
    void draw();
    void resetPos(){this->m_MMatrix = glm::mat4(1);};
    void translate(const glm::vec3 vec){this->m_MMatrix = glm::translate(this->m_MMatrix,vec);};
    void rotate();
    void scale();
    const glimac::ShapeVertex* getDataPointer() const;
    GLsizei                    getVertexCount() const;
};

#endif // PROJET_DM_QUENTIN_LEBON_MODEL_HPP
