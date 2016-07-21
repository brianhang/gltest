#include "material.h"

Material::Material(std::string shaderName, std::string diffuseName,
std::string specularName) :
shader("shaders/" + shaderName + ".vert", "shaders/" + shaderName + ".frag"),
diffuse("textures/" + diffuseName),
specular("textures/" + specularName) {
    shader.bind();
    shader.setUniform("baseTexture", 0);
    shader.setUniform("specularMap", 1);
}

GLvoid Material::bind() {
    shader.bind();
    diffuse.bind(0);
    specular.bind(1);
}

Shader &Material::getShader() {
    return shader;
}