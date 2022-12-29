//
// Created by lebonq on 20/12/22.
//

#ifndef PROJET_DM_QUENTIN_LEBON_UTIL_HPP
#define PROJET_DM_QUENTIN_LEBON_UTIL_HPP

#ifndef NDEBUG
#define DEBUG_PRINT(x) std::cout << x;
#else
#define DEBUG_PRINT(x)
#endif

#define PRINT(x) std::cout << x;

#include "glm/glm.hpp"
#include "iomanip"
#include "iostream"
#include "string"
#include "third-party/ppmio/include/ppm_io.h"
#include "vector"


class Util {


public:
    static std::vector<uint> readImageFile(const std::string filePath,int * width, int* height);
    static uint RGB_to_hexa(unsigned int R, unsigned int G, unsigned int B);
    static glm::mat4 resetPos(){return glm::mat4(1);};
    static float                   calcAngle(const glm::vec3& a, const glm::vec3& b);
};

#endif // PROJET_DM_QUENTIN_LEBON_UTIL_HPP
