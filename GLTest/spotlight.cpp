#include "spotlight.h"

GLvoid SpotLight::bindValues(Shader &shader, std::string &data) {
    BIND_LIGHT_VALUE(cone);
    BIND_LIGHT_VALUE(outerCone);
    BIND_LIGHT_VALUE(constant);
    BIND_LIGHT_VALUE(linear);
    BIND_LIGHT_VALUE(quadratic);
    BIND_LIGHT_VALUE(position);
    BIND_LIGHT_VALUE(direction);
}

GLvoid SpotLight::setPosition(glm::vec3 newPosition) {
    position = newPosition;
}

GLvoid SpotLight::setDirection(glm::vec3 newDirection) {
    direction = glm::normalize(newDirection);
}

GLvoid SpotLight::setCone(GLfloat angle) {
    cone = glm::cos(glm::radians(angle));
}

GLvoid SpotLight::setOuterCone(GLfloat angle) {
    outerCone = glm::cos(glm::radians(angle));
}

GLvoid SpotLight::setConstant(GLfloat value) {
    constant = value;
}

GLvoid SpotLight::setLinear(GLfloat value) {
    linear = value;
}

GLvoid SpotLight::setQuadratic(GLfloat value) {
    quadratic = value;
}

GLfloat SpotLight::getCone() {
    return cone;
}

GLfloat SpotLight::getOuterCone() {
    return outerCone;
}

GLfloat SpotLight::getConstant() {
    return constant;
}

GLfloat SpotLight::getLinear() {
    return linear;
}

GLfloat SpotLight::getQuadratic() {
    return quadratic;
}

const GLchar *SpotLight::getType() {
    return "spotLight";
}

glm::vec3 SpotLight::getPosition() {
    return position;
}

glm::vec3 SpotLight::getDirection() {
    return direction;
}
