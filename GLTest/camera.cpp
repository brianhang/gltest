#include "camera.h"

#define PI 3.14159265358979323846f
#define HALF_PI (PI / 2)

Camera::Camera() {
    pitch = 0;
    yaw = 0;

    forward = glm::vec3(0.0f, 0.0f, -1.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0f);
    right = glm::normalize(glm::cross(up, forward));
}

void Camera::setDirection(const glm::vec3 &direction) {
    forward = glm::normalize(direction);
    right = glm::normalize(glm::cross(up, forward));

    view = glm::lookAt(position, position + forward, up);
}

void Camera::lookAt(const glm::vec3 &target) {
    setDirection(target - position);
}

void Camera::setPosition(glm::vec3 newPosition) {
    position = newPosition;
    view = glm::lookAt(position, position + forward, up);
}

void Camera::setAngles(const glm::vec2 &angles) {
    yaw = glm::radians(angles[0]);
    pitch = glm::radians(-angles[1]);
    
    if (pitch >= HALF_PI) {
        pitch = HALF_PI - 0.001f;
    } else if (pitch <= -HALF_PI) {
        pitch = -HALF_PI + 0.001f;
    }
  
    forward[0] = glm::cos(pitch) * std::cos(yaw);
    forward[1] = glm::sin(pitch);
    forward[2] = glm::cos(pitch) * std::sin(yaw);

    forward = glm::normalize(forward);
    right = glm::normalize(glm::cross(up, forward));

    view = glm::lookAt(position, position + forward, up);
}

void Camera::rotate(const glm::vec2 &angles) {
    setAngles(glm::vec2(glm::degrees(yaw), glm::degrees(-pitch)) + angles);
}

void Camera::setFOV(GLfloat newFOV) {
    FOV = glm::radians(newFOV);
    projection = glm::perspective(FOV,
                                  (GLfloat)width / height, nearZ, farZ);
}

void Camera::move(const glm::vec3 &direction) {
    position += (forward * direction.z)
                + (up * direction.y)
                + (right * direction.x);

    view = glm::lookAt(position, position + forward, up);
}

void Camera::setNearZ(GLfloat newNearZ) {
    nearZ = newNearZ;
    projection = glm::perspective(FOV, (GLfloat)width / height, 0.1f, 100.0f);
}

void Camera::setFarZ(GLfloat newFarZ) {
    farZ = newFarZ;
    projection = glm::perspective(FOV, (GLfloat)width / height, 0.1f, 100.0f);
}

void Camera::setViewSize(GLint newWidth, GLint newHeight) {
    width = newWidth;
    height = newHeight;

    projection = glm::perspective(FOV, (GLfloat)width / height, 0.1f, 100.0f);
}

GLint Camera::getViewWidth() {
    return width;
}

GLint Camera::getViewHeight() {
    return height;
}

GLfloat Camera::getFOV() {
    return glm::degrees(FOV);
}

GLfloat Camera::getNearZ() {
    return nearZ;
}

GLfloat Camera::getFarZ() {
    return farZ;
}

glm::vec3 Camera::getPosition() {
    return position;
}

glm::vec3 Camera::getForward() {
    return forward;
}

glm::vec3 Camera::getUp() {
    return up;
}

glm::vec3 Camera::getRight() {
    return right;
}

glm::mat4 Camera::getViewMatrix() {
    return view;
}

glm::mat4 Camera::getProjectionMatrix() {
    return projection;
}