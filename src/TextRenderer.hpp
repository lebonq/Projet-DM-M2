//
// Created by lebonq on 28/12/22.
//

#ifndef PROJET_DM_QUENTIN_LEBON_TEXTRENDERER_HPP
#define PROJET_DM_QUENTIN_LEBON_TEXTRENDERER_HPP

#include <ft2build.h>
#include FT_FREETYPE_H
#include <string>
#include <iostream>
#include <glimac/glm.hpp>
#include <map>
#include <glad/glad.h>
#include <glimac/Program.hpp>

struct Character {
    unsigned int TextureID;  // ID handle of the glyph texture
    glm::ivec2   Size;       // Size of glyph
    glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
    long Advance;    // Offset to advance to next glyph

};

class TextRenderer {
private:
    std::map<char, Character> m_characters;
    GLuint m_VAO;
    GLuint m_VBO;
    glimac::Program m_shader;
    glm::mat4 m_projection;
    int m_windowWidth;
    int m_windowHeight;
public:
    TextRenderer(int windowWidth, int windowHeight);
    ~TextRenderer();
    void renderText(const std::string& text, float x, float y, float scale, glm::vec3 color);
};

#endif // PROJET_DM_QUENTIN_LEBON_TEXTRENDERER_HPP
