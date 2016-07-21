#pragma once

#define GLEW_STATIC

#include <GL/glew.h>
#include <SOIL.h>
#include "shader.h"

class Texture2D {
private:
    GLuint textureID;
    GLint width;
    GLint height;
    GLint channels;

public:
    Texture2D(const std::string &path, GLint forceChannels = GL_RGB);
    ~Texture2D();
    GLvoid bind(GLuint location = 0);
    GLuint getID();
};