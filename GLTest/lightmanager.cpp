#include "lightmanager.h"

LightManager::LightManager() {
    directionalLightCount = 0;
    pointLightCount = 0;
    spotLightCount = 0;
}

GLvoid LightManager::bind(Shader &shader) {
    shader.setUniform("viewPos", viewPos);
    shader.setUniform("dirLightCount", (GLint) directionalLightCount);
    shader.setUniform("pointLightCount", (GLint) pointLightCount);
    shader.setUniform("spotLightCount", (GLint) spotLightCount);

    GLubyte i;

    for (i = 0; i < spotLightCount; i++) {
        spotLights[i]->bind(shader);
    }

    for (i = 0; i < directionalLightCount; i++) {
        directionalLights[i]->bind(shader);
    }

    for (i = 0; i < pointLightCount; i++) {
        pointLights[i]->bind(shader);
    }
}

GLvoid LightManager::setViewPos(glm::vec3 newViewPos) {
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

PointLight *LightManager::getPointLight(GLubyte index) {
    if (index >= pointLightCount) {
        return NULL;
    }

    return pointLights[index];
}

DirectionalLight *LightManager::createDirectionalLight() {
    if (directionalLightCount >= MAX_DIR_LIGHTS) {
        return NULL;
    }

    DirectionalLight *light = new DirectionalLight(directionalLightCount);

    directionalLights[directionalLightCount] = light;
    directionalLightCount++;

    return light;
}

DirectionalLight *LightManager::getDirectionalLight(GLubyte index) {
    if (index >= directionalLightCount) {
        return NULL;
    }

    return directionalLights[index];
}

SpotLight *LightManager::createSpotLight() {
    if (spotLightCount >= MAX_SPOT_LIGHTS) {
        return NULL;
    }

    SpotLight *light = new SpotLight(spotLightCount);

    spotLights[spotLightCount] = light;
    spotLightCount++;

    return light;
}

SpotLight *LightManager::getSpotLight(GLubyte index) {
    if (index >= spotLightCount) {
        return NULL;
    }

    return spotLights[index];
}