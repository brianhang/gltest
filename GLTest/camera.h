#pragma once

#define GLEW_STATIC

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
private:
    glm::mat4 view;
    glm::mat4 projection;
    glm::vec3 position;
    glm::vec3 up;
    glm::vec3 forward;
    glm::vec3 right;
    float FOV;
    float nearZ;
    float farZ;
    int width;
    int height;

public:
    Camera(int newWidth, int newHeight, float newFOV, float newNearZ = 0.1f,
           float newFarZ = 100.0f);
    void setDirection(const glm::vec3 &direction);
    void lookAt(const glm::vec3 &target);
    void setPosition(glm::vec3 newPosition);
    void setAngles(const glm::vec3 &angles);
    void setFOV(float newFOV);
    void setNearZ(float newNearZ);
    void setFarZ(float newFarZ);
    void setViewSize(int newWidth, int newHeight);
    void move(const glm::vec3 &direction);
    int getViewWidth();
    int getViewHeight();
    float getFOV();
    float getNearZ();
    float getFarZ();
    glm::vec3 getPosition();
    glm::vec3 getForward();
    glm::vec3 getUp();
    glm::vec3 getRight();
    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();
};