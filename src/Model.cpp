//
// Created by lebonq on 20/12/22.
//

#include "Model.hpp"

Model::Model(const int ID, const GLuint texID, ShadersManager* mShaderProgram)
    : m_shaderProgram(mShaderProgram)
{
    DEBUG_PRINT("Build a Model " << std::endl);
    this->m_ID           = ID;
    this->m_Vertices     = DM_PROJECT_MODEL_VERTICES[this->m_ID];
    this->m_ibos         = DM_PROJECT_MODEL_INDICES[this->m_ID];
    this->m_nVertexCount = static_cast<GLsizei>(m_Vertices.size());
    this->m_textureId    = texID;
    this->m_ks           = DM_PROJECT_MODEL_KS[ID];
    this->m_kd           = DM_PROJECT_MODEL_KD[ID];
    this->m_shininess    = DM_PROJECT_MODEL_SHININESS[ID];

    glGenBuffers(1, &this->m_vbo);
    glGenVertexArrays(1, &this->m_vao);
    glGenBuffers(1, &this->m_ibo);

    glBindBuffer(GL_ARRAY_BUFFER, this->m_vbo);
    glBufferData(GL_ARRAY_BUFFER, this->m_nVertexCount * sizeof(glimac::ShapeVertex), this->getDataPointer(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0); // Un-bind our VBO from the arra_buffer

    // Generate an index buffer object (IBO) and bind it

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_ibo);
    // Set the index data for the IBO
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->m_ibos.size() * sizeof(unsigned int), this->m_ibos.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindVertexArray(this->m_vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_ibo);

    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);   // set the position for the vao
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);     // set the position for the vao
    glEnableVertexAttribArray(VERTEX_ATTR_TEX_COORDS); // set the position for the vao

    glBindBuffer(GL_ARRAY_BUFFER, this->m_vbo);

    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);                       // Say to the gpu how to use the VBO to draw position
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));     // Say to the gpu how to use the VBO to draw color
    glVertexAttribPointer(VERTEX_ATTR_TEX_COORDS, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat))); // Say to the gpu how to use the VBO to draw color

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
// Renvoit le pointeur vers les données
const glimac::ShapeVertex* Model::getDataPointer() const
{
    return &this->m_Vertices[0];
}

Model::~Model()
{
    DEBUG_PRINT("Delete a Model " << std::endl);
    glDeleteBuffers(1, &this->m_vbo);
    glDeleteBuffers(1, &this->m_ibo);
    glDeleteVertexArrays(1, &this->m_vao);
}
void Model::draw(const glm::mat4& mmatrix)
{
    glUniformMatrix4fv(this->m_shaderProgram->getMMatrix(), 1, GL_FALSE, glm::value_ptr(mmatrix));
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(this->m_ibos.size()), GL_UNSIGNED_INT, 0);
}

void Model::bindModel()
{
    glBindVertexArray(this->m_vao);
    glUniform3fv(this->m_shaderProgram->getKd(), 1, glm::value_ptr(this->m_kd));
    glUniform3fv(this->m_shaderProgram->getKs(), 1, glm::value_ptr(this->m_ks));
    glUniform1fv(this->m_shaderProgram->getShininess(), 1, &this->m_shininess);
    glBindTexture(GL_TEXTURE_2D, this->m_textureId);
    glUniform1i(this->m_shaderProgram->getTexLoc(), 0);
}

void Model::unBindModel()
{
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
}
