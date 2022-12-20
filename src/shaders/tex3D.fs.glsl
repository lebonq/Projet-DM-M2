#version 330 core

in vec3 vPosition_vs; // Position du sommet transformé dans l'espace View
in vec3 vNormal_vs; // Normale du sommet transformé dans l'espace View
in vec2 vTexCoords; // Coordonnées de texture du sommet

out vec3 fFragColor;

uniform sampler2D uTex_data;

void main() {
    vec4 tex = texture(uTex_data,vTexCoords);
    fFragColor = tex.xyz;
}