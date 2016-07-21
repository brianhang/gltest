#include "pointlight.h"

GLvoid PointLight::setPosition(glm::vec3 newPosition) {
    position = newPosition;
}

GLvoid PointLight::setConstant(GLfloat newConstant) {
    constant = newConstant;
}

GLvoid PointLight::setLinear(GLfloat newLinear) {
    linear = newLinear;
}

GLvoid PointLight::setQuadratic(GLfloat newQuadratic) {
    quadratic = newQuadratic;
}

GLvoid PointLight::bindValues(Shader &shader, std::string &data) {
    BIND_LIGHT_VALUE(position);
    BIND_LIGHT_VALUE(constant);
    BIND_LIGHT_VALUE(linear);
    BIND_LIGHT_VALUE(quadratic);
}

GLfloat PointLight::getConstant() {
    return constant;
}

GLfloat PointLight::getLinear() {
    return linear;
}

GLfloat PointLight::getQuadratic() {
    return quadratic;
}

const GLchar *PointLight::getType() {
    return "pointLight";
}

glm::vec3 PointLight::getPositon() {
    return position;
}