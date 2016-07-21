#pragma once

#include "light.h"

class DirectionalLight : public Light {
private:
    glm::vec3 direction;

protected:
    GLvoid bindValues(Shader &shader, std::string &data);

public:
    using Light::Light;

    GLvoid setDirection(const glm::vec3 &newDirection);
    const GLchar *getType();
    glm::vec3 getDirection();
};

