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
    GLfloat FOV;
    GLfloat nearZ;
    GLfloat farZ;
    GLfloat pitch;
    GLfloat yaw;
    GLint width;
    GLint height;

public:
    Camera();
    GLvoid setDirection(const glm::vec3 &direction);
    GLvoid lookAt(const glm::vec3 &target);
    GLvoid setPosition(glm::vec3 newPosition);
    GLvoid setAngles(const glm::vec2 &angles);
    GLvoid setFOV(GLfloat newFOV);
    GLvoid setNearZ(GLfloat newNearZ);
    GLvoid setFarZ(GLfloat newFarZ);
    GLvoid setViewSize(GLint newWidth, GLint newHeight);
    GLvoid move(const glm::vec3 &direction);
    GLvoid rotate(const glm::vec2 &angles);
    GLint getViewWidth();
    GLint getViewHeight();
    GLfloat getFOV();
    GLfloat getNearZ();
    GLfloat getFarZ();
    glm::vec3 getPosition();
    glm::vec3 getForward();
    glm::vec3 getUp();
    glm::vec3 getRight();
    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();
};