#version 330 core

in vec3 vPosition_vs; // Position du sommet transformé dans l'espace View
in vec3 vNormal_vs; // Normale du sommet transformé dans l'espace View
in vec2 vTexCoords; // Coordonnées de texture du sommet

out vec3 fFragColor;

uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;

uniform vec4 uLightDir_vs; //position de la lumiere transformé dans l'espace View
uniform vec3 uLightIntensity;

uniform sampler2D uTex_data;

vec3 blinnPhong(){
    vec3 w0 = normalize(-vPosition_vs);
    vec3 halfVector = (w0+uLightDir_vs.xyz)/2;
    vec3 color = uLightIntensity*(uKd*(dot(uLightDir_vs.xyz,vNormal_vs))+uKs*pow(dot(halfVector,vNormal_vs),uShininess));
    return color;
}

void main() {
    vec4 tex = texture(uTex_data,vTexCoords);
    fFragColor = tex.xyz * blinnPhong();
}