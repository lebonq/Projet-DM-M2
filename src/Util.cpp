//
// Created by lebonq on 20/12/22.
//

#include "Util.hpp"

uint Util::RGB_to_hexa(unsigned int R, unsigned int G, unsigned int B) {
    return (R << 16) | (G << 8) | B;
}

std::vector<uint> Util::readImageFile(const std::string filePath,int * width, int* height){
    PPM ppmIn(filePath);
    // Get image height
    *height = ppmIn.getH();
    // Get image width
    *width =  ppmIn.getW();
    // Get image handler
    uint8_t * pImage = ppmIn.getImageHandler();
    uint8_t R,G,B;
    std::vector<uint> data;
    for (int i = 0; i < (*width * *height)*3; i+=3) {
            R = pImage[i];
            G = pImage[i+1];
            B = pImage[i+2];
            data.push_back(Util::RGB_to_hexa(R,G,B));
            if((i/3)%10 == 0)DEBUG_PRINT(std::endl);
            DEBUG_PRINT(std::hex << std::setw(6) << std::setfill('0')
              << data[i/3] << "|");
    }
    return data;
}
