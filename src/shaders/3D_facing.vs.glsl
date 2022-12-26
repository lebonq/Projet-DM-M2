#version 330 core

layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexNormal;
layout(location = 2) in vec2 aVertexTexCoords;

//Matric de transfo
uniform mat4 uMMatrix;
uniform mat4 uVMatrix;
uniform mat4 uPMatrix;

uniform vec3 uPlayerPos;

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

//from here https://www.neilmendoza.com/glsl-rotation-about-an-arbitrary-axis/
mat4 rotationMatrix(vec3 axis, float angle)
{
    axis = normalize(axis);
    float s = sin(angle);
    float c = cos(angle);
    float oc = 1.0 - c;

    return mat4(oc * axis.x * axis.x + c,           oc * axis.x * axis.y - axis.z * s,  oc * axis.z * axis.x + axis.y * s,  0.0,
                oc * axis.x * axis.y + axis.z * s,  oc * axis.y * axis.y + c,           oc * axis.y * axis.z - axis.x * s,  0.0,
                oc * axis.z * axis.x - axis.y * s,  oc * axis.y * axis.z + axis.x * s,  oc * axis.z * axis.z + c,           0.0,
                0.0,                                0.0,                                0.0,                                1.0);
}

float calcAngle(vec3 a, vec3 b) {
  float dotProduct = dot(a, b);
  float aMagnitude = length(a);
  float bMagnitude = length(b);

  float cosine = dotProduct / (aMagnitude * bMagnitude);
  return acos(cosine);
}

void main() {
        // Passage en coordonnées homogènes
    vec4 vertexPosition = vec4(aVertexPosition, 1);
    vec4 vertexNormal = vec4(aVertexNormal, 0);


    vec4 vPosition_mm = uMMatrix * vertexPosition;
    vec2 to_player = uPlayerPos.xz - vPosition_mm.xz;
    vec2 to_one = vec2(vPosition_mm.x,vPosition_mm.z+1) - vPosition_mm.xz;
    float angle_rot = calcAngle(vec3(to_player,0),vec3(to_one,0));
    //to orient angle
    if(uPlayerPos.x > vPosition_mm.x){
        angle_rot = -angle_rot;
    }

    mat4 rotated_MMatrix = uMMatrix * rotationMatrix(vec3(0,1,0),radians(degrees(angle_rot)+0));

    // Calcul des valeurs de sortie
    vPosition_vs = vec3(uVMatrix * rotated_MMatrix * vertexPosition);
    vNormal_vs = vec3(transpose(inverse(uVMatrix*rotated_MMatrix)) * vertexNormal);
    vTexCoords = aVertexTexCoords;

    // Calcul de la position projetée
    gl_Position = uPMatrix * uVMatrix * rotated_MMatrix * vertexPosition;
}