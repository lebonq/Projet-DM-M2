//
// Created by lebonq on 20/12/22.
//

#ifndef PROJET_DM_QUENTIN_LEBON_DATA_HPP
#define PROJET_DM_QUENTIN_LEBON_DATA_HPP

#include "glad/glad.h"

const GLuint VERTEX_ATTR_POSITION = 0;
const GLuint VERTEX_ATTR_NORMAL = 1;
const GLuint VERTEX_ATTR_TEX_COORDS = 2;

const int DM_PROJECT_COLOR_WALL = 0xFFFFFF;
const int DM_PROJECT_COLOR_EMPTY = 0x000000;
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

const std::vector<std::string> DM_PROJECT_TEX = {"assets/textures/Brick/Brick_08-512x512.png"/*Wall Texture in 0*/
                                                 ,"assets/textures/Tile/Tile_19-512x512.png"/*Floor texture in 1*/};



#endif // PROJET_DM_QUENTIN_LEBON_DATA_HPP
