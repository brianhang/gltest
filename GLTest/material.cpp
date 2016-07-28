#include "material.h"

Material::Material(std::string shaderName, std::string diffuseName,
std::string specularName, std::string normalName) :
shader("shaders/" + shaderName + ".vert", "shaders/" + shaderName + ".frag"),
diffuse("textures/" + diffuseName),
specular("textures/" + specularName),
normal("textures/" + normalName) {
    shader.bind();
    shader.setUniform("baseTexture", 0);
    shader.setUniform("specularMap", 1);
    shader.setUniform("normalMap", 2);
}

GLvoid Material::bind() {
    shader.bind();
    diffuse.bind(0);
    specular.bind(1);
    normal.bind(2);
}

Shader &Material::getShader() {
    return shader;
}