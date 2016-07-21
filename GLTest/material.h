#pragma once

#include <string>
#include "texture2d.h"
#include "shader.h"

class Material {
    Shader shader;
    Texture2D diffuse;
    Texture2D specular;

public:
    Material(std::string shaderName, std::string diffuseName,
             std::string specularName);
    GLvoid bind();
    Shader &getShader();
};

