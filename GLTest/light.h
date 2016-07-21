#pragma once

#define GLEW_STATIC

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include "shader.h"

#define BIND_LIGHT_VALUE(name) (shader.setUniform((data + #name).c_str(), (name)))

class Light {
private:
    GLubyte index;
    virtual GLvoid bindValues(Shader &shader, std::string &data) = 0;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

public:
    Light(GLubyte newIndex = 0,
          glm::vec3 newDiffuse = glm::vec3(1.0f, 1.0f, 1.0f),
          glm::vec3 newAmbient = glm::vec3(0.0f, 0.0f, 0.0f),
          glm::vec3 newSpecular = glm::vec3(1.0f, 1.0f, 1.0f));
    GLvoid bind(Shader &shader);
    GLvoid setAmbient(glm::vec3 value);
    GLvoid setDiffuse(glm::vec3 value);
    GLvoid setSpecular(glm::vec3 specular);
    virtual const GLchar *getType();
    GLubyte getIndex();
    glm::vec3 getAmbient();
    glm::vec3 getDiffuse();
    glm::vec3 getSpecular();
};