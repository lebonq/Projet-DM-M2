#version 330 core

layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexNormal;
layout(location = 2) in vec2 aVertexTexCoords;

//Matric de transfo
uniform mat4 uMMatrix;
uniform mat4 uVMatrix;
uniform mat4 uPMatrix;

out vec3 vPosition_vs; // Position du sommet transformé dans l'espace View
out vec3 vNormal_vs; // Normale du sommet transformé dans l'espace View
out vec2 vTexCoords; // Coordonnées de texture du sommet


mat3 translate(float tx, float ty) {
    return mat3(vec3(1,0,0),vec3(0,1,0),vec3(tx,ty,1));
}

mat3 scale(float sx, float sy) {
    return mat3(vec3(sx,0,0),vec3(0,sy,0),vec3(0,0,1));
}

mat3 rotation(float alpha) {
    return mat3(vec3(cos(alpha),sin(alpha),0),vec3(-sin(alpha),cos(alpha),0),vec3(0,0,1));
}

void main() {
    // Passage en coordonnées homogènes
    vec4 vertexPosition = vec4(aVertexPosition, 1);
    vec4 vertexNormal = vec4(aVertexNormal, 0);

    // Calcul des valeurs de sortie
    vPosition_vs = vec3(uMMatrix * uVMatrix * vertexPosition);
    vNormal_vs = vec3(transpose(inverse(uMMatrix*uVMatrix)) * vertexNormal);
    vTexCoords = aVertexTexCoords;

    // Calcul de la position projetée
    gl_Position = uPMatrix * uVMatrix * uMMatrix * vertexPosition;
}