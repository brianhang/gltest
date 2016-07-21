#pragma once

#define GLEW_STATIC

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>

class Shader {
private:
    GLuint program;

public:
    Shader(const std::string &vertName, const std::string &fragName);
    ~Shader();
    GLvoid bind();
    GLvoid setUniform(const GLchar *name, GLfloat v);
    GLvoid setUniform(const GLchar *name, GLuint v);
    GLvoid setUniform(const GLchar *name, GLint v);
    GLvoid setUniform(const GLchar *name, const glm::vec4 &v);
    GLvoid setUniform(const GLchar *name, const glm::vec3 &v);
    GLvoid setUniform(const GLchar *name, const glm::mat4 &v);
};