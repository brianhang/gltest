#pragma once

#define GLEW_STATIC

#include <GL/glew.h>
#include <SOIL.h>

class Texture2D {
private:
    GLuint textureID;
    int width;
    int height;
    int channels;

public:
    Texture2D(const char *path, GLint forceChannels = SOIL_LOAD_RGB);
    ~Texture2D();
    void bind(GLuint location = 0);
    GLuint getID();
};