//
// Created by lebonq on 20/12/22.
//

#include "TexturesManager.hpp"

TexturesManager::TexturesManager()
{
    DEBUG_PRINT("Build TextureManager " << std::endl);
    for (auto image : DM_PROJECT_TEX) {
        std::unique_ptr<glimac::Image> tex_image = glimac::loadImage(image);
        // Generate texture
        GLuint tex_id;
        glGenTextures(1, &tex_id);
        glBindTexture(GL_TEXTURE_2D, tex_id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex_image.get()->getWidth(), tex_image.get()->getHeight(), 0, GL_RGBA, GL_FLOAT, tex_image.get()->getPixels());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);
        // Add texture into the manage at the right index
        this->m_texIds.push_back(tex_id);
        tex_image = nullptr;
        DEBUG_PRINT("Load texture " + image << std::endl)
    }
}

TexturesManager::~TexturesManager()
{
    DEBUG_PRINT("Delete TextureManager " << std::endl);
    glDeleteTextures(static_cast<GLsizei>(this->m_texIds.size()), this->m_texIds.data());
}
GLuint TexturesManager::getTexId(const int ID)
{
    return this->m_texIds[ID];
}
