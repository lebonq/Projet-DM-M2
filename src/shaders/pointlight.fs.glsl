#version 330 core

in vec3 vPosition_vs;// Position du sommet transformé dans l'espace View
in vec3 vNormal_vs;// Normale du sommet transformé dans l'espace View
in vec2 vTexCoords;// Coordonnées de texture du sommet

out vec4 fFragColor;

uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;
uniform float uRedness;

uniform vec3 uLightPos_vs;//position de la lumiere transformé dans l'espace View
uniform vec3 uLightIntensity;

uniform sampler2D uTex_data;

vec3 blinnPhong(){
    vec3 w0 = normalize(-vPosition_vs);
    vec3 halfVector = (w0+normalize(uLightPos_vs - vPosition_vs))/2.0f;
    float d = distance(uLightPos_vs, vPosition_vs);
    vec3 corrected_intensity = clamp(uLightIntensity/(d*d), 0.0, 1.0);
    vec3 color = clamp(corrected_intensity*(uKd * max(dot(normalize(uLightPos_vs - vPosition_vs), vNormal_vs), 0.0) + uKs * pow(max(dot(halfVector, vNormal_vs), 0.0), uShininess)), 0.0, 1.0);
    return color;
}


void main() {
    vec4 tex = texture(uTex_data, vTexCoords);
    fFragColor = clamp(tex*vec4(blinnPhong(), 1), 0.0f, 1.0f)*vec4(1.0f+uRedness, 1.0f-uRedness, 1.0f-uRedness, 1.0f);
}