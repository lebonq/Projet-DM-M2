#version 330 core
in vec2 vTexCoords;
out vec4 fFragColor;

uniform sampler2D uText;
uniform vec4 uTextColor;

void main()
{
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(uText, vTexCoords).r);
    fFragColor = uTextColor * sampled;
}