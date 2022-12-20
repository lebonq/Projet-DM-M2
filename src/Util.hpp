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

#include "iostream"
#include "string"
#include "vector"
#include "iomanip"
#include "third-party/ppmio/include/ppm_io.h"

class Util {
public:
    static std::vector<uint> readImageFile(const std::string filePath,int * width, int* height);
    static uint RGB_to_hexa(unsigned int R, unsigned int G, unsigned int B);
};

#endif // PROJET_DM_QUENTIN_LEBON_UTIL_HPP
