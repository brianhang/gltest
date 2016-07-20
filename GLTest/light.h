#pragma once

#define GLEW_STATIC

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include "shader.h"

#define BIND_LIGHT_VALUE(name) (shader.setUniform((data + #name).c_str(), (name)))

class Light {
private:
    int index;
    virtual void bindValues(Shader &shader, std::string &data) = 0;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

public:
    Light(int newIndex,
          glm::vec3 newDiffuse = glm::vec3(1.0f, 1.0f, 1.0f),
          glm::vec3 newAmbient = glm::vec3(0.0f, 0.0f, 0.0f),
          glm::vec3 newSpecular = glm::vec3(1.0f, 1.0f, 1.0f));
    void bind(Shader &shader);
    void setAmbient(glm::vec3 value);
    void setDiffuse(glm::vec3 value);
    void setSpecular(glm::vec3 specular);
    virtual const char *getType();
    glm::vec3 getAmbient();
    glm::vec3 getDiffuse();
    glm::vec3 getSpecular();
};