#include "camera.h"

Camera::Camera(int newWidth, int newHeight, float newFOV, float newNearZ,
float newFarZ) {
    width = newWidth;
    height = newHeight;
    nearZ = newNearZ;
    farZ = newFarZ;
    FOV = newFOV;
    up = glm::vec3(0.0f, 1.0f, 0.0f);

    projection = glm::perspective(FOV, (float)width / height, nearZ, farZ);
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

void Camera::setAngles(const glm::vec3 &angles) {
    float pitch = glm::radians(angles[0]);
    float yaw = glm::radians(angles[1]);

    forward[0] = std::cos(pitch) * std::cos(yaw);
    forward[1] = std::sin(pitch);
    forward[2] = std::cos(pitch) * std::sin(yaw);

    forward = glm::normalize(forward);
    right = glm::normalize(glm::cross(up, forward));

    view = glm::lookAt(position, position + forward, up);
}

void Camera::setFOV(float newFOV) {
    FOV = newFOV;
    projection = glm::perspective(FOV, (float)width / height, nearZ, farZ);
}

void Camera::move(const glm::vec3 &direction) {
    position += (forward * direction[0])
                + (up * direction[1])
                + (right * direction[2]);

    view = glm::lookAt(position, position + forward, up);
}

void Camera::setNearZ(float newNearZ) {
    nearZ = newNearZ;
    projection = glm::perspective(FOV, (float)width / height, 0.1f, 100.0f);
}

void Camera::setFarZ(float newFarZ) {
    farZ = newFarZ;
    projection = glm::perspective(FOV, (float)width / height, 0.1f, 100.0f);
}

void Camera::setViewSize(int newWidth, int newHeight) {
    width = newWidth;
    height = newHeight;

    projection = glm::perspective(FOV, (float)width / height, 0.1f, 100.0f);
}

int Camera::getViewWidth() {
    return width;
}

int Camera::getViewHeight() {
    return height;
}

float Camera::getFOV() {
    return FOV;
}

float Camera::getNearZ() {
    return nearZ;
}

float Camera::getFarZ() {
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