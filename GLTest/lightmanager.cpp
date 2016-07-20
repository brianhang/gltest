#include "lightmanager.h"

LightManager::LightManager() {
    dirLightCount = 0;
    pointLightCount = 0;
    spotLightCount = 0;
}

void LightManager::bind(Shader &shader) {
    shader.setUniform("viewPos", viewPos);

    int i;
    /*
    for (i = 0; i < dirLightCount; i++) {
        dirLights[i]->bind(shader);
    }

    for (i = 0; i < spotLightCount; i++) {
        spotLights[i]->bind(shader);
    }
    */

    for (i = 0; i < pointLightCount; i++) {
        pointLights[i]->bind(shader);
    }
}

void LightManager::setViewPos(glm::vec3 newViewPos) {
    viewPos = newViewPos;
}

PointLight *LightManager::createPointLight() {
    if (pointLightCount >= MAX_POINT_LIGHTS) {
        return NULL;
    }

    PointLight *light = new PointLight(pointLightCount);

    pointLights[pointLightCount] = light;
    pointLightCount++;

    return light;
}