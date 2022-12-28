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
const int DM_PROJECT_MAP_SHADOW = 6;

//in json those are the "type" field
const int DM_PROJECT_ITEM_GOLDCOIN = 0;

const int DM_PROJECT_MONSTER_SKELETON = 0;

//In json this is the "model_id" field
const int DM_PROJECT_ID_MANAGER_WALL = 0; //Index of the wall texture in the Texture Manager
const int DM_PROJECT_ID_MANAGER_FLOOR = 1;
const int DM_PROJECT_ID_MANAGER_WATER = 2;
const int DM_PROJECT_ID_MANAGER_GOLDCOIN = 3;
const int DM_PROJECT_ID_MANAGER_SHADOW = 4;
const int DM_PROJECT_ID_MANAGER_SKELETON = 5;
const int DM_PROJECT_ID_MANAGER_DOOR = 6;
const int DM_PROJECT_ID_MANAGER_FLOOR_HOLE = 7;
const int DM_PROJECT_ID_MANAGER_LADDER= 8;

const std::vector<std::string> DM_PROJECT_TEX = {"assets/textures/static_object/wall.png"/*Wall Texture in 0*/
                                                 ,"assets/textures/static_object/floor.png"/*Floor texture in 1*/
                                                 ,"assets/textures/static_object/water.png"
                                                 ,"assets/textures/money/Gold-coin.png"
                                                 ,"assets/textures/shadow.png"
                                                 ,"assets/textures/Skeleton.png"
                                                 ,"assets/textures/static_object/door.png"
                                                 ,"assets/textures/static_object/floor_hole.png",
                                                 "assets/textures/ladder.png"};

const std::vector<std::vector<glimac::ShapeVertex>> DM_PROJECT_MODEL_VERTICES = {{
             glimac::ShapeVertex{glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)},  // bottom left
             glimac::ShapeVertex{glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)},  // bottom right
             glimac::ShapeVertex{glm::vec3(0.5f,  0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)},  // top right
             glimac::ShapeVertex{glm::vec3(-0.5f,  0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)}   // top left
    },{
             glimac::ShapeVertex{glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f)},  // bottom left
             glimac::ShapeVertex{glm::vec3(0.5f, 0.0f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)},  // bottom right
             glimac::ShapeVertex{glm::vec3(0.5f,  0.0f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f)},  // top right
             glimac::ShapeVertex{glm::vec3(-0.5f,  0.0f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)}   // top left
    },{
             glimac::ShapeVertex{glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f)},  // bottom left
             glimac::ShapeVertex{glm::vec3(0.5f, 0.0f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)},  // bottom right
             glimac::ShapeVertex{glm::vec3(0.5f,  0.0f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f)},  // top right
             glimac::ShapeVertex{glm::vec3(-0.5f,  0.0f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)}   // top left
    },{
             glimac::ShapeVertex{glm::vec3(-0.25f, -0.25f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)},  // bottom left
             glimac::ShapeVertex{glm::vec3(0.25f, -0.25f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)},  // bottom right
             glimac::ShapeVertex{glm::vec3(0.25f,  0.25f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)},  // top right
             glimac::ShapeVertex{glm::vec3(-0.25f,  0.25f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)}   // top left
    },{
             glimac::ShapeVertex{glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f)},  // bottom left
             glimac::ShapeVertex{glm::vec3(0.5f, 0.0f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)},  // bottom right
             glimac::ShapeVertex{glm::vec3(0.5f,  0.0f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f)},  // top right
             glimac::ShapeVertex{glm::vec3(-0.5f,  0.0f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)}   // top left
    },{
             glimac::ShapeVertex{glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)},  // bottom left
             glimac::ShapeVertex{glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)},  // bottom right
             glimac::ShapeVertex{glm::vec3(0.5f,  0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)},  // top right
             glimac::ShapeVertex{glm::vec3(-0.5f,  0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)}   // top left
    },{
             glimac::ShapeVertex{glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)},  // bottom left
             glimac::ShapeVertex{glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)},  // bottom right
             glimac::ShapeVertex{glm::vec3(0.5f,  0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)},  // top right
             glimac::ShapeVertex{glm::vec3(-0.5f,  0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)},   // top left
                                                                                     //opposite normal
             glimac::ShapeVertex{glm::vec3(-0.5f, -0.5f, -0.01f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 0.0f)},  // bottom left
             glimac::ShapeVertex{glm::vec3(0.5f, -0.5f, -0.01f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 0.0f)},  // bottom right
             glimac::ShapeVertex{glm::vec3(0.5f,  0.5f, -0.01f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 1.0f)},  // top right
             glimac::ShapeVertex{glm::vec3(-0.5f,  0.5f, -0.01f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 1.0f)}   // top left
    },{
             glimac::ShapeVertex{glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f)},  // bottom left
             glimac::ShapeVertex{glm::vec3(0.5f, 0.0f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)},  // bottom right
             glimac::ShapeVertex{glm::vec3(0.5f,  0.0f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f)},  // top right
             glimac::ShapeVertex{glm::vec3(-0.5f,  0.0f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)}   // top left
    },{                                                                             //Oriented in Z
             glimac::ShapeVertex{glm::vec3(-0.18f, -1.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)},  // bottom left
             glimac::ShapeVertex{glm::vec3(0.18f, -1.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)},  // bottom right
             glimac::ShapeVertex{glm::vec3(0.18f,  1.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)},  // top right
             glimac::ShapeVertex{glm::vec3(-0.18f,  1.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)}
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
},{
    0, 1, 2,  // first triangle
    2, 3, 0   // second triangle
},{
    0, 1, 2,  // first triangle
    2, 3, 0   // second triangle
},{
    0, 1, 2,  // first triangle
    2, 3, 0   // second triangle
},{
    0, 1, 2,  // first triangle
    2, 3, 0,   // second triangle
    4, 5, 6,  // third triangle
    6, 7, 4   // fourth triangle
},{
    0, 1, 2,  // first triangle
    2, 3, 0   // second triangle
},{
    0, 1, 2,  // first triangle
    2, 3, 0   // second triangle
}};

const std::vector<glm::vec3> DM_PROJECT_MODEL_KD = {glm::vec3(2), //0
                                                           glm::vec3(2),
                                                           glm::vec3(9),
                                                           glm::vec3(3),
                                                           glm::vec3(2),
                                                           glm::vec3(2),
                                                           glm::vec3(2),//6
                                                           glm::vec3(2),//7
                                                           glm::vec3(2)};

const std::vector<glm::vec3> DM_PROJECT_MODEL_KS = {glm::vec3(0),
                                                    glm::vec3(0),
                                                    glm::vec3(18),
                                                    glm::vec3(2),
                                                    glm::vec3(0),
                                                    glm::vec3(0),
                                                    glm::vec3(0),//6
                                                    glm::vec3(0),//7
                                                    glm::vec3(0)};

const std::vector<float> DM_PROJECT_MODEL_SHININESS = {2,2,8,4,2,2,2,2,2};


#endif // PROJET_DM_QUENTIN_LEBON_DATA_HPP
