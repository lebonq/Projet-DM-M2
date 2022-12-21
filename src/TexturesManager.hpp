//
// Created by lebonq on 20/12/22.
//

#ifndef PROJET_DM_QUENTIN_LEBON_TEXTURESMANAGER_HPP
#define PROJET_DM_QUENTIN_LEBON_TEXTURESMANAGER_HPP

#include <glad/glad.h>
#include <glimac/Image.hpp>
#include <vector>

#include "Data.hpp"
#include "Util.hpp"

class TexturesManager {
private:
    std::vector<GLuint> m_texIds;
public:
    TexturesManager();
    ~TexturesManager();
    GLuint getTexId(const int ID);
};

#endif // PROJET_DM_QUENTIN_LEBON_TEXTURESMANAGER_HPP
