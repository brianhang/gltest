#pragma once

#include "pointlight.h"

#define MAX_DIR_LIGHTS 8
#define MAX_POINT_LIGHTS 8
#define MAX_SPOT_LIGHTS 8

class LightManager {
    int pointLightCount;
    int spotLightCount;
    int dirLightCount;
    PointLight *pointLights[MAX_POINT_LIGHTS];
    glm::vec3 viewPos;

public:
    LightManager();
    void bind(Shader &shader);
    void setViewPos(glm::vec3 newViewPos);
    PointLight *createPointLight();
};

