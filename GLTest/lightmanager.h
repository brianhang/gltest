#pragma once

#include "pointlight.h"
#include "directionallight.h"
#include "spotlight.h"

#define MAX_DIR_LIGHTS 8
#define MAX_POINT_LIGHTS 8
#define MAX_SPOT_LIGHTS 8

class LightManager {
    GLubyte directionalLightCount;
    GLubyte pointLightCount;
    GLubyte spotLightCount;
    DirectionalLight *directionalLights[MAX_DIR_LIGHTS];
    PointLight *pointLights[MAX_POINT_LIGHTS];
    SpotLight *spotLights[MAX_SPOT_LIGHTS];
    glm::vec3 viewPos;

public:
    LightManager();
    GLvoid bind(Shader &shader);
    GLvoid setViewPos(glm::vec3 newViewPos);
    PointLight *createPointLight();
    PointLight *getPointLight(GLubyte index);
    DirectionalLight *createDirectionalLight();
    DirectionalLight *getDirectionalLight(GLubyte index);
    SpotLight *createSpotLight();
    SpotLight *getSpotLight(GLubyte index);
};

