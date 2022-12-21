//
// Created by lebonq on 20/12/22.
//

#ifndef PROJET_DM_QUENTIN_LEBON_DATA_HPP
#define PROJET_DM_QUENTIN_LEBON_DATA_HPP

#include "glad/glad.h"
#include "glimac/common.hpp"
#include <vector>
#include <string>

const GLuint VERTEX_ATTR_POSITION = 0;
const GLuint VERTEX_ATTR_NORMAL = 1;
const GLuint VERTEX_ATTR_TEX_COORDS = 2;

const int DM_PROJECT_COLOR_WALL = 0x000000;
const int DM_PROJECT_COLOR_EMPTY = 0xFFFFFF;
const int DM_PROJECT_COLOR_DOOR = 0xAA7722;
const int DM_PROJECT_COLOR_WATER = 0x0000FF;
const int DM_PROJECT_COLOR_ENTRANCE = 0xFF0000;
const int DM_PROJECT_COLOR_EXIT = 0x00FF00;

const int DM_PROJECT_MAP_WALL = 0;
const int DM_PROJECT_MAP_EMPTY = 1;
const int DM_PROJECT_MAP_DOOR = 2;
const int DM_PROJECT_MAP_WATER = 3;
const int DM_PROJECT_MAP_ENTRANCE = 4;
const int DM_PROJECT_MAP_EXIT = 5;

const int DM_PROJECT_ID_MANAGER_WALL = 0; //Index of the wall texture in the Texture Manager
const int DM_PROJECT_ID_MANAGER_FLOOR = 1;
const int DM_PROJECT_ID_MANAGER_WATER = 2;

const std::vector<std::string> DM_PROJECT_TEX = {"assets/textures/Brick/Brick_08-512x512.png"/*Wall Texture in 0*/
                                                ,"assets/textures/Tile/Tile_19-512x512.png"/*Floor texture in 1*/
                                                ,"assets/textures/Elements/Elements_15-512x512.png"};

const std::vector<std::vector<glimac::ShapeVertex>> DM_PROJECT_MODEL_VERTICES = {{
             glimac::ShapeVertex{glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)},  // bottom left
             glimac::ShapeVertex{glm::vec3( 0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)},  // bottom right
             glimac::ShapeVertex{glm::vec3( 0.5f,  0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)},  // top right
             glimac::ShapeVertex{glm::vec3(-0.5f,  0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)}   // top left
    },{
             glimac::ShapeVertex{glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f)},  // bottom left
             glimac::ShapeVertex{glm::vec3( 0.5f, 0.0f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)},  // bottom right
             glimac::ShapeVertex{glm::vec3( 0.5f,  0.0f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f)},  // top right
             glimac::ShapeVertex{glm::vec3(-0.5f,  0.0f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)}   // top left
    },{
             glimac::ShapeVertex{glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f)},  // bottom left
             glimac::ShapeVertex{glm::vec3( 0.5f, 0.0f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)},  // bottom right
             glimac::ShapeVertex{glm::vec3( 0.5f,  0.0f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f)},  // top right
             glimac::ShapeVertex{glm::vec3(-0.5f,  0.0f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)}   // top left
    }};

const std::vector<std::vector<unsigned int>> DM_PROJECT_MODEL_INDICES = {{
    0, 1, 2,  // first triangle
    2, 3, 0   // second triangle
},{
    0, 1, 2,  // first triangle
    2, 3, 0   // second triangle
},{
    0, 1, 2,  // first triangle
    2, 3, 0   // second triangle
}};



#endif // PROJET_DM_QUENTIN_LEBON_DATA_HPP
