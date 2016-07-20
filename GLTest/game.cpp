#include "game.h"
#include <iostream>

#define GAME_TITLE "OpenGL Test"
#define SCR_W 800
#define SCR_H 600

Game::Game() {
    if (window.open(GAME_TITLE, SCR_W, SCR_H, true)) {
        window.center();

        Input::getInstance().setWindow(window.getGLFWWindow());
    }
}

bool Game::initialize() {
    if (!window.isOpen()) {
        return false;
    }

    window.center();

    camera.setViewSize(window.getWidth(), window.getHeight());
    camera.setNearZ(0.1f);
    camera.setFarZ(100.0f);
    camera.setFOV(45);

    // Drawing stuff.
    GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Vertex Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // Vertex Normal
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // Texture Coordinate
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    Shader test("shaders/default.vert", "shaders/default.frag");
    Texture2D testImg("images/test.png");

    camera.move(glm::vec3(0.0f, 0.0f, -2.0f));

    float i = 0.0f;

    Input::getInstance().setMouseEnabled(false);

    PointLight *light0 = lightManager.createPointLight();
    light0->setPosition(camera.getPosition());
    light0->setConstant(1.0f);
    light0->setLinear(0.09f);
    light0->setQuadratic(0.032f);

    glEnable(GL_DEPTH_TEST);

    // Game loop.
    while (window.isOpen()) {
        // Get user input.
        Input::getInstance().poll();

        if (Input::getInstance().isKeyDown(GLFW_KEY_ESCAPE)) {
            break;
        }

        lightManager.setViewPos(camera.getPosition());

        // Render the game.
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        update(0.0f);

        camera.rotate(glm::vec2(Input::getInstance().getMouseDeltaX() * 0.05f,
                                Input::getInstance().getMouseDeltaY() * 0.05f));
        render();

        testImg.bind();

        i += 0.2f;

        glm::mat4 model;
        model = glm::rotate(model, glm::radians(i), glm::vec3(0.0f, 1.0f, 0.0f));

        test.setUniform("projection", camera.getProjectionMatrix());
        test.setUniform("view", camera.getViewMatrix());
        test.setUniform("model", model);
        test.setUniform("offset", glm::vec3(glfwGetTime() * 0.1f, 0, 0));

        lightManager.bind(test);

        test.bind();

        if (Input::getInstance().isKeyDown(GLFW_KEY_W)) {
            camera.move(glm::vec3(0.0f, 0.0f, 0.05f));
        } else if (Input::getInstance().isKeyDown(GLFW_KEY_S)) {
            camera.move(glm::vec3(0.0f, 0.0f, -0.05f));
        }

        if (Input::getInstance().isKeyDown(GLFW_KEY_A)) {
            camera.move(glm::vec3(0.05f, 0.0f, 0.0f));
        } else if (Input::getInstance().isKeyDown(GLFW_KEY_D)) {
            camera.move(glm::vec3(-0.05f, 0.0f, 0.0f));
        }

        if (Input::getInstance().isKeyDown(GLFW_KEY_SPACE)) {
            camera.move(glm::vec3(0.0f, 0.05f, 0.0f));
        }

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);

        window.display();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    return true;
}

void Game::update(float deltaTime) {

}

void Game::render() {
    /*
    */
}

Game::~Game() {
}