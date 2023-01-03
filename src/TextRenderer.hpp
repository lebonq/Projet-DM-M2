//
// Created by lebonq on 28/12/22.
//

#ifndef PROJET_DM_QUENTIN_LEBON_TEXTRENDERER_HPP
#define PROJET_DM_QUENTIN_LEBON_TEXTRENDERER_HPP

#include <ft2build.h>
#include FT_FREETYPE_H
#include <glad/glad.h>
#include <glimac/Program.hpp>
#include <glimac/glm.hpp>
#include <iostream>
#include <map>
#include <string>

struct Character {
    unsigned int TextureID; // ID handle of the glyph texture
    glm::ivec2   Size;      // Size of glyph
    glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
    long         Advance;   // Offset to advance to next glyph
};

class TextRenderer {
private:
    std::map<char, Character> m_characters;
    GLuint                    m_VAO;
    GLuint                    m_VBO;
    glimac::Program           m_shader;
    glm::mat4                 m_projection;
    int                       m_windowWidth;
    int                       m_windowHeight;

public:
    /**
     * @source https://learnopengl.com/In-Practice/Text-Rendering
     * @param windowWidth
     * @param windowHeight
     */
    TextRenderer(int windowWidth, int windowHeight);
    ~TextRenderer();
    /**
     * Create the associated quads and draw it on the sreen
     * @source https://learnopengl.com/In-Practice/Text-Rendering
     */
    void renderText(const std::string& text, float x, float y, float scale, glm::vec4 color);
    /**
     * Allow us to update the projection matrix to place text on different part of the screen
     * @param PMatrix
     */
    void updatePMatrix(glm::mat4 PMatrix) { this->m_projection = PMatrix; }
    /**
     * Allow us to compute the size in px of a string
     * @param text
     * @param scale
     * @return The width in pixel of the text
     */
    float getSizeText(const std::string& text, float scale);
};

#endif // PROJET_DM_QUENTIN_LEBON_TEXTRENDERER_HPP
