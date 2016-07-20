#include "pointlight.h"

void PointLight::setPosition(glm::vec3 newPosition) {
    position = newPosition;
}

void PointLight::setConstant(float newConstant) {
    constant = newConstant;
}

void PointLight::setLinear(float newLinear) {
    linear = newLinear;
}

void PointLight::setQuadratic(float newQuadratic) {
    quadratic = newQuadratic;
}

void PointLight::bindValues(Shader &shader, std::string &data) {
    BIND_LIGHT_VALUE(position);
    BIND_LIGHT_VALUE(constant);
    BIND_LIGHT_VALUE(linear);
    BIND_LIGHT_VALUE(quadratic);
}

float PointLight::getConstant() {
    return constant;
}

float PointLight::getLinear() {
    return linear;
}

float PointLight::getQuadratic() {
    return quadratic;
}

const char *PointLight::getType() {
    return "pointLight";
}

glm::vec3 PointLight::getPositon() {
    return position;
}