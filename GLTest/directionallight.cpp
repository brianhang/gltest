#include "directionallight.h"

void DirectionalLight::bindValues(Shader &shader, std::string &data) {
    BIND_LIGHT_VALUE(direction);
}

void DirectionalLight::setDirection(const glm::vec3 &newDirection) {
    direction = glm::normalize(newDirection);
}

const char *DirectionalLight::getType() {
    return "dirLight";
}

glm::vec3 DirectionalLight::getDirection() {
    return direction;
}