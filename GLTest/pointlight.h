#pragma once

#include "light.h"

class PointLight : public Light {
private:
    float constant;
    float linear;
    float quadratic;
    glm::vec3 position;

public:
    using Light::Light;

    void bindValues(Shader &shader, std::string &data);
    void setPosition(glm::vec3 newPosition);
    void setConstant(float newConstant);
    void setLinear(float newLinear);
    void setQuadratic(float newQuadratic);
    const char *getType();
    float getConstant();
    float getLinear();
    float getQuadratic();
    glm::vec3 getPositon();
};