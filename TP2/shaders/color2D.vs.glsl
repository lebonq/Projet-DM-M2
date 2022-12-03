#version 330 core

layout(location = 0) in vec2 aVertexPosition;
layout(location = 1) in vec3 aVertexColor;

out vec3 vFragColor;
out vec2 vPosT;

mat3 translate(float tx, float ty) {
    return mat3(vec3(1,0,0),vec3(0,1,0),vec3(tx,ty,1));
};

mat3 scale(float sx, float sy) {
    return mat3(vec3(sx,0,0),vec3(0,sy,0),vec3(0,0,1));
};

mat3 rotation(float alpha) {
    return mat3(vec3(cos(alpha),sin(alpha),0),vec3(-sin(alpha),cos(alpha),0),vec3(0,0,1));
};

void main() {
    vec2 transformed = (scale(10,10) * vec3(aVertexPosition, 1)).xy;
    gl_Position = vec4(transformed, 0, 1);
    vFragColor = aVertexColor;
    vPosT = aVertexPosition;
};