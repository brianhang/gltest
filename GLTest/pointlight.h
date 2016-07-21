#pragma once

#include "light.h"

class PointLight : public Light {
private:
    GLfloat constant;
    GLfloat linear;
    GLfloat quadratic;
    glm::vec3 position;

protected:
    GLvoid bindValues(Shader &shader, std::string &data);

public:
    using Light::Light;

    GLvoid setPosition(glm::vec3 newPosition);
    GLvoid setConstant(GLfloat newConstant);
    GLvoid setLinear(GLfloat newLinear);
    GLvoid setQuadratic(GLfloat newQuadratic);
    const GLchar *getType();
    GLfloat getConstant();
    GLfloat getLinear();
    GLfloat getQuadratic();
    glm::vec3 getPositon();
};