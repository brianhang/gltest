#include "light.h"
#include <iostream>

Light::Light(int newIndex, glm::vec3 newDiffuse, glm::vec3 newAmbient,
glm::vec3 newSpecular) {
    diffuse = newDiffuse;
    ambient = newAmbient;
    specular = newSpecular;

    index = newIndex;
}

void Light::bind(Shader &shader) {
    std::string i = std::to_string(index);
    std::string data = getType();
    data += "[" + i + "].";

    BIND_LIGHT_VALUE(diffuse);
    BIND_LIGHT_VALUE(ambient);
    BIND_LIGHT_VALUE(specular);

    bindValues(shader, data);
}

void Light::setAmbient(glm::vec3 value) {
    ambient = value;
}

void Light::setDiffuse(glm::vec3 value) {
    diffuse = value;
}

void Light::setSpecular(glm::vec3 value) {
    specular = value;
}

const char *Light::getType() {
    return "light";
}

glm::vec3 Light::getAmbient() {
    return ambient;
}

glm::vec3 Light::getDiffuse() {
    return diffuse;
}

glm::vec3 Light::getSpecular() {
    return specular;
}