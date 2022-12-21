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

    int m_textureId;
    ShadersManager& m_shaderProgram; //Not owning pointer

    glm::vec3 m_kd;
    glm::vec3 m_ks;
    GLfloat m_shininess;

    glm::mat4 m_MMatrix;

    GLuint m_vbo;
    GLuint m_vao;
    GLuint m_ibo;
public:
    Model(const int ID, const GLuint texID, ShadersManager& mShaderProgram);
    ~Model();
    void draw();
    void resetPos(){this->m_MMatrix = glm::mat4(1);};
    void translate(const glm::vec3 vec){this->m_MMatrix = glm::translate(this->m_MMatrix,vec);};
    /*
     * Rotate Model byt given angle on the given axis
     */
    void rotate(const float angle,const glm::vec3 axis){this->m_MMatrix = glm::rotate(this->m_MMatrix, glm::radians(angle), axis);}; // Translation * Rotation};
    void scale(const glm::vec3 vec){this->m_MMatrix = glm::scale(this->m_MMatrix, vec);};
    const glimac::ShapeVertex* getDataPointer() const;
    GLsizei                    getVertexCount() const;
};

#endif // PROJET_DM_QUENTIN_LEBON_MODEL_HPP
