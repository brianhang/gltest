#pragma once

#define GLEW_STATIC

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "shader.h"
#include "texture2d.h"

enum TextureType {
    DIFFUSE = 0,
    SPECULAR = 1,
    NORMAL = 2,
    SHINY = 3
};

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoord;
};

struct Texture {
    GLuint id;
    TextureType type;
};

class Mesh {
private:
    GLvoid setup();
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;
    std::vector<GLuint> indices;
    std::vector<Vertex> vertices;
    std::vector<Texture> textures;
    std::vector<GLfloat> shininess;

public:
    Mesh(std::vector<GLuint> newIndices, std::vector<Vertex> newVertices,
         std::vector<Texture> newTextures,
         std::vector<GLfloat> newShininess);
    GLvoid draw(Shader &shader);
};

