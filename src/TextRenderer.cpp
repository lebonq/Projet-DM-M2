//
// Created by lebonq on 28/12/22.
//

#include "TextRenderer.hpp"
TextRenderer::TextRenderer(int window_width, int window_height)
{
    this->m_projection   = glm::ortho(0.0f, static_cast<float>(200), 0.0f, static_cast<float>(200));
    this->m_windowWidth  = window_width;
    this->m_windowHeight = window_height;

    FT_Library ft;
    FT_Face    face;

    if (FT_Init_FreeType(&ft)) {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        exit(-1);
    }
    if (FT_New_Face(ft, "assets/fonts/DUNG.TTF", 0, &face)) {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        exit(-1);
    }
    FT_Set_Pixel_Sizes(face, 296, 296);
    if (FT_Load_Char(face, 'X', FT_LOAD_RENDER)) {
        std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
        exit(-1);
    }

    // here we generate the quads and texture for every first 128 characters and put it in a map
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

    unsigned int texture;
    for (unsigned char c = 0; c < 128; c++) {
        // load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        // generate texture
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer);
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // now store character for later use
        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x};
        this->m_characters.insert(std::pair<char, Character>(c, character));
    }
    // destroy the face and the library
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    glGenVertexArrays(1, &this->m_VAO);
    glGenBuffers(1, &this->m_VBO);
    glBindVertexArray(this->m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    this->m_shader = glimac::loadProgram("src/shaders/text.vs.glsl", "src/shaders/text.fs.glsl");
}

TextRenderer::~TextRenderer()
{
    glDeleteBuffers(1, &this->m_VBO);
    glDeleteVertexArrays(1, &this->m_VAO);
    for (auto it = this->m_characters.begin(); it != this->m_characters.end(); ++it) {
        glDeleteTextures(1, &it->second.TextureID);
    }
}
void TextRenderer::renderText(const std::string& text, float x, float y, float scale, glm::vec4 color)
{
    // activate corresponding render state
    this->m_shader.use();
    glUniformMatrix4fv(glGetUniformLocation(this->m_shader.getGLId(), "uPMatrix"), 1, GL_FALSE, glm::value_ptr(this->m_projection));
    glUniform4fv(glGetUniformLocation(this->m_shader.getGLId(), "uTextColor"), 1, glm::value_ptr(color));
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(this->m_VAO);

    // iterate through all characters
    std::string::const_iterator c;
    float                       w, h, xpos, ypos;
    for (c = text.begin(); c != text.end(); c++) {
        Character ch = this->m_characters[*c];

        xpos = x + ch.Bearing.x * scale;
        ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        w = ch.Size.x * scale;
        h = ch.Size.y * scale;
        // update VBO for each character
        float vertices[6][4] = {
            {xpos, ypos + h, 0.0f, 0.0f},
            {xpos, ypos, 0.0f, 1.0f},
            {xpos + w, ypos, 1.0f, 1.0f},

            {xpos, ypos + h, 0.0f, 0.0f},
            {xpos + w, ypos, 1.0f, 1.0f},
            {xpos + w, ypos + h, 1.0f, 0.0f}};
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        glUniform1i(glGetUniformLocation(this->m_shader.getGLId(), "uText"), 0);
        glBindBuffer(GL_ARRAY_BUFFER, this->m_VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        x += (ch.Advance >> 6) * scale;
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

float TextRenderer::getSizeText(const std::string& text, float scale)
{
    std::string::const_iterator c;
    float                       w_tot      = 0.f;
    float                       xpos_begin = 0.f;
    float                       xpos_end   = 0.f;
    float                       x          = 0.f;
    for (c = text.begin(); c != text.end(); c++) {
        Character ch = this->m_characters[*c];
        if (c == text.begin()) {
            xpos_begin = x + ch.Bearing.x * scale;
        }
        if (c == text.end()) {
            xpos_end = x + ch.Bearing.x * scale;
        }
        w_tot += ch.Size.x * scale;
        x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
        xpos_end = x;
    }
    return xpos_end - xpos_begin;
}