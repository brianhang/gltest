#pragma once

#define GLEW_STATIC

#include <GL/glew.h>
#include <glm/glm.hpp>

class Shader {
private:
    GLuint program;

public:
    Shader(const GLchar *vertName, const GLchar *fragName);
    ~Shader();
    void bind();
    void setUniform(const GLchar *name, float v);
    void setUniform(const GLchar *name, const glm::vec4 &v);
    void setUniform(const GLchar *name, const glm::vec3 &v);
    void setUniform(const GLchar *name, const glm::mat4 &v);
};