#include "light.h"

Light::Light(GLubyte newIndex, glm::vec3 newDiffuse, glm::vec3 newAmbient,
glm::vec3 newSpecular) {
    diffuse = newDiffuse;
    ambient = newAmbient;
    specular = newSpecular;

    index = newIndex;
}

GLvoid Light::bind(Shader &shader) {
    std::string i = std::to_string(index);
    std::string data = getType();
    data += "[" + i + "].";

    BIND_LIGHT_VALUE(diffuse);
    BIND_LIGHT_VALUE(ambient);
    BIND_LIGHT_VALUE(specular);

    bindValues(shader, data);
}

GLvoid Light::setAmbient(glm::vec3 value) {
    ambient = value;
}

GLvoid Light::setDiffuse(glm::vec3 value) {
    diffuse = value;
}

GLvoid Light::setSpecular(glm::vec3 value) {
    specular = value;
}

const GLchar *Light::getType() {
    return "light";
}

GLubyte Light::getIndex() {
    return index;
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