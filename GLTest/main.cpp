#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include "window.h"
#include "shader.h"
#include "texture2d.h"
#include "camera.h"

#define SCR_W 800
#define SCR_H 600

int main(int argc, char *argv[]) {
    // Create the game window.
    Window window("OpenGL Test", 800, 600);

    if (!window.open()) {
        return EXIT_FAILURE;
    }

    window.center();

    // Drawing stuff.
    GLfloat triangle[] = {
        0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // Top Right
        0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f, 1.0f, // Bottom Right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, // Bottom Left
        -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f  // Top Left 
    };

    GLushort indices[] = {
        0, 1, 3,   // First Triangle
        1, 2, 3    // Second Triangle
    };

    GLuint VBO, VAO, EBO;

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    Shader test("shaders/default.vert", "shaders/default.frag");
    Texture2D testImg("images/test.png");

    // Game loop.
    while (window.isOpen()) {
        // Update game state.
        window.pollEvents();

        // Render the game.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        testImg.bind();
        test.setUniform("offset", glm::vec3(glfwGetTime() * 0.1f, 0, 0));
        test.bind();

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
        glBindVertexArray(0);

        window.display();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    return EXIT_SUCCESS;
}