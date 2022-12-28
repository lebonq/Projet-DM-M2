
#version 330 core
layout (location = 0) in vec4 aVertexAndTexPosition; //xy pos and zw tex
out vec2 vTexCoords;

uniform mat4 uPMatrix;

void main()
{
    gl_Position = uPMatrix * vec4(aVertexAndTexPosition.xy, 0.0, 1.0);
    vTexCoords = aVertexAndTexPosition.zw;
}  