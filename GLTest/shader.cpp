#include "shader.h"
#include <fstream>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

#define LOG_SIZE 512

Shader::Shader(const std::string &vertName, const std::string &fragName) {
    program = 0;

    // Open the vertex shader file.
    std::ifstream vertStream("shaders/" + vertName + ".vs", std::ifstream::in);
    vertStream.exceptions(std::ifstream::badbit);

    // Open the fragment shader file.
    std::ifstream fragStream("shaders/" + fragName + ".fs", std::ifstream::in);
    fragStream.exceptions(std::ifstream::badbit);

    try {
        // Read the contents of both shader files.
        std::string vertData(std::istreambuf_iterator<char>(vertStream),
            (std::istreambuf_iterator<char>()));
        std::string fragData(std::istreambuf_iterator<char>(fragStream),
            (std::istreambuf_iterator<char>()));

        const GLchar *vertSource = vertData.c_str();
        const GLchar *fragSource = fragData.c_str();

        // Shader compilation logging.
        GLint success;
        GLchar log[LOG_SIZE];

        // Try to compile the vertex shader.
        GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertShader, 1, &vertSource, NULL);
        glCompileShader(vertShader);

        glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);

        // Error if the vertex shader failed to compile.
        if (!success) {
            glGetShaderInfoLog(vertShader, LOG_SIZE, NULL, log);

            std::cerr << "Shader::Shader(" << vertName << ", " << fragName
                      << ") failed to compile vertex shader! " << std::endl
                      << log << std::endl;
        }
        
        // Try to compile the fragment shader.
        GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragShader, 1, &fragSource, NULL);
        glCompileShader(fragShader);

        glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);

        // Error if the fragment shader failed to compile.
        if (!success) {
            glGetShaderInfoLog(fragShader, LOG_SIZE, NULL, log);

            std::cerr << "Shader::Shader(" << vertName << ", " << fragName
                << ") failed to compile fragment shader! " << std::endl << log
                << std::endl;
        }

        // Create the program for the shaders.
        program = glCreateProgram();

        // Attach and link the shaders to the program.
        glAttachShader(program, vertShader);
        glAttachShader(program, fragShader);
        glLinkProgram(program);

        // Error if the program failed to link.
        glGetProgramiv(program, GL_LINK_STATUS, &success);

        if (!success) {
            glGetProgramInfoLog(program, LOG_SIZE, NULL, log);

            std::cerr << "Shader::Shader(" << vertName << ", " << fragName
                << ") failed to link program! " << std::endl << log
                << std::endl;
        }

        // Clean up the shaders.
        glDeleteShader(vertShader);
        glDeleteShader(fragShader);
    } catch (std::ifstream::failure e) {
        std::cerr << "Shader::Shader(" << vertName << ", " << fragName
                  << ") failed to read data!" << std::endl;
    }
}

GLvoid Shader::bind() {
    glUseProgram(program);
}

GLvoid Shader::setUniform(const GLchar *name, GLfloat v) {
    glUniform1f(glGetUniformLocation(program, name), v);
}

GLvoid Shader::setUniform(const GLchar * name, GLuint v) {
    glUniform1ui(glGetUniformLocation(program, name), v);
}

GLvoid Shader::setUniform(const GLchar * name, GLint v){
    glUniform1i(glGetUniformLocation(program, name), v);
}

GLvoid Shader::setUniform(const GLchar *name, const glm::vec4 &v) {
    glUniform4f(glGetUniformLocation(program, name), v[0], v[1], v[2], v[3]);
}

GLvoid Shader::setUniform(const GLchar *name, const glm::vec3 &v) {
    glUniform3f(glGetUniformLocation(program, name), v[0], v[1], v[2]);
}

GLvoid Shader::setUniform(const GLchar *name, const glm::mat4 &v) {
    glUniformMatrix4fv(glGetUniformLocation(program, name), 1, GL_FALSE,
                       glm::value_ptr(v));
}

Shader::~Shader() {
    if (program) {
        glDeleteProgram(program);
    }
}
