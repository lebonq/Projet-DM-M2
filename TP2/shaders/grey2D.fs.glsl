#version 330 core

in vec3 vFragColor;
in vec2 vPosT;

out vec3 fFragColor;

void main() {
    float a = 1*exp(-100*(distance(vPosT,vec2(0,0))*distance(vPosT,vec2(0,0))));
    fFragColor = vFragColor*a;
};