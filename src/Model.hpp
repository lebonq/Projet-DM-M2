//
// Created by lebonq on 20/12/22.
//

#ifndef PROJET_DM_QUENTIN_LEBON_MODEL_HPP
#define PROJET_DM_QUENTIN_LEBON_MODEL_HPP

#include "vector"
#include "glad/glad.h"
#include "glimac/common.hpp"
#include "Data.hpp"

class Model {
private:
    glimac::ShapeVertex* m_Vertices;
    std::vector<unsigned int> m_ibos;
    glm::mat4 m_MMatrix;
    GLsizei m_nVertexCount; // Nombre de sommets
    int m_textureId;
    GLuint m_vbo;
    GLuint m_vao;
    GLuint m_ibo;
public:
    Model(glimac::ShapeVertex* vertices, std::vector<unsigned int> ibo,int nb_vertices, GLuint texID);
    ~Model();
    void draw();
    void translate();
    void rotate();
    void scale();
    const glimac::ShapeVertex* getDataPointer() const;
    GLsizei                    getVertexCount() const;
};

#endif // PROJET_DM_QUENTIN_LEBON_MODEL_HPP
