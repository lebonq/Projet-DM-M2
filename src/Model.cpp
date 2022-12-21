//
// Created by lebonq on 20/12/22.
//

#include "Model.hpp"
Model::Model(glimac::ShapeVertex* vertices, const std::vector<unsigned int> ibo, const int nb_vertices, const GLuint texID)
{
    this->m_Vertices = vertices;
    this->m_ibos = ibo;
    this->m_nVertexCount = nb_vertices;
    this->m_textureId = texID;

    glGenBuffers(1,&this->m_vbo);
    glGenVertexArrays(1,&this->m_vao);
    glGenBuffers(1, &this->m_ibo);

    glBindBuffer(GL_ARRAY_BUFFER,this->m_vbo);
    glBufferData(GL_ARRAY_BUFFER,this->m_nVertexCount*sizeof(glimac::ShapeVertex), this->m_Vertices,GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER,0);//Un-bind our VBO from the arra_buffer

    // Generate an index buffer object (IBO) and bind it

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_ibo);
    // Set the index data for the IBO
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->m_ibos.size() * sizeof(unsigned int), this->m_ibos.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindVertexArray(this->m_vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_ibo);

    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);//set the position for the vao
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);//set the position for the vao
    glEnableVertexAttribArray(VERTEX_ATTR_TEX_COORDS);//set the position for the vao

    glBindBuffer(GL_ARRAY_BUFFER,this->m_vbo);

    glVertexAttribPointer(VERTEX_ATTR_POSITION,3,GL_FLOAT,GL_FALSE,8*sizeof(GLfloat),(GLvoid*)0);//Say to the gpu how to use the VBO to draw position
    glVertexAttribPointer(VERTEX_ATTR_NORMAL,3,GL_FLOAT,GL_FALSE,8*sizeof(GLfloat),(GLvoid*)(3*sizeof(GLfloat)));//Say to the gpu how to use the VBO to draw color
    glVertexAttribPointer(VERTEX_ATTR_TEX_COORDS,2,GL_FLOAT,GL_FALSE,8*sizeof(GLfloat),(GLvoid*)(6*sizeof(GLfloat)));//Say to the gpu how to use the VBO to draw color

    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);

}
// Renvoit le pointeur vers les données
const glimac::ShapeVertex* Model::getDataPointer() const {
    return &this->m_Vertices[0];
}

// Renvoit le nombre de vertex
GLsizei Model::getVertexCount() const {
    return this->m_nVertexCount;
}

Model::~Model()
{
    /*glDeleteVertexArrays(1, &this->m_vao);
    glDeleteBuffers(1, &this->m_vbo);
    glDeleteBuffers(1, &this->m_ibo);*/
}
void Model::draw()
{
    glBindVertexArray(this->m_vao);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
    glBindVertexArray(0);
}
