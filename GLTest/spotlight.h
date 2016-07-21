#pragma once

#include "light.h"

class SpotLight : public Light {
private:
    GLfloat cone;
    GLfloat outerCone;
    GLfloat constant;
    GLfloat linear;
    GLfloat quadratic;
    glm::vec3 position;
    glm::vec3 direction;
    
protected:
    void bindValues(Shader &shader, std::string &data);

public:
    using Light::Light;

    GLvoid setCone(GLfloat angle);
    GLvoid setOuterCone(GLfloat angle);
    GLvoid setConstant(GLfloat value);
    GLvoid setLinear(GLfloat value);
    GLvoid setQuadratic(GLfloat value);
    GLvoid setDirection(glm::vec3 newDirection);
    GLvoid setPosition(glm::vec3 newPosition);
    GLfloat getCone();
    GLfloat getOuterCone();
    GLfloat getConstant();
    GLfloat getLinear();
    GLfloat getQuadratic();
    const GLchar *getType();
    glm::vec3 getPosition();
    glm::vec3 getDirection();
};