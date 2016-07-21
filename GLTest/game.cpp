#include "game.h"
#include <iostream>

#define GAME_TITLE "OpenGL Test"
#define SCR_W 800
#define SCR_H 600

Game::Game() {
    if (window.open(GAME_TITLE, SCR_W, SCR_H, GL_TRUE)) {
        window.center();

        Input::getInstance().setWindow(window.getGLFWWindow());
    }

    flashlightOn = GL_TRUE;
}

GLboolean Game::initialize() {
    if (!window.isOpen()) {
        return GL_FALSE;
    }

    window.center();

    camera.setViewSize(window.getWidth(), window.getHeight());
    camera.setNearZ(0.1f);
    camera.setFarZ(100.0f);
    camera.setFOV(45);

    // Drawing stuff.
    GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
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

    Material test("default", "container2.png", "container2_specular.png");

    camera.move(glm::vec3(0.0f, 0.0f, -2.0f));

    GLfloat i = 0.0f;

    Input::getInstance().setMouseEnabled(GL_FALSE);

    PointLight *light0 = lightManager.createPointLight();
    light0->setPosition(glm::vec3(-2.0f, 1.0f, 2.0f));
    light0->setConstant(1.0f);
    light0->setLinear(0.09f);
    light0->setQuadratic(0.032f);
    light0->setDiffuse(glm::vec3(0.0f, 0.0f, 1.0f));
    light0->setSpecular(light0->getDiffuse());

    PointLight *light2 = lightManager.createPointLight();
    light2->setPosition(glm::vec3(-2.0f, 1.0f, -2.0f));
    light2->setConstant(1.0f);
    light2->setLinear(0.09f);
    light2->setQuadratic(0.032f);
    light2->setDiffuse(glm::vec3(0.0f, 1.0f, 0.0f));
    light2->setSpecular(light2->getDiffuse());
    
    PointLight *light3 = lightManager.createPointLight();
    light3->setPosition(glm::vec3(2.0f, 1.0f, 2.0f));
    light3->setConstant(1.0f);
    light3->setLinear(0.09f);
    light3->setQuadratic(0.032f);
    light3->setDiffuse(glm::vec3(1.0f, 0.0f, 0.0f));
    light3->setSpecular(light3->getDiffuse());

    DirectionalLight *light1 = lightManager.createDirectionalLight();
    light1->setDirection(glm::vec3(0.0f, -0.8f, -1.0f));
    light1->setDiffuse(glm::vec3(1.0f, 1.0f, 1.0f));

    SpotLight *light4 = lightManager.createSpotLight();
    light4->setConstant(1.0f);
    light4->setLinear(0.0014f);
    light4->setQuadratic(0.000007f);
    light4->setDiffuse(glm::vec3(1.0f, 1.0f, 1.0f));
    light4->setCone(10);
    light4->setOuterCone(16);

    glEnable(GL_DEPTH_TEST);

    // Game loop.
    while (window.isOpen()) {
        // Get user input.
        Input::getInstance().poll();

        if (Input::getInstance().isKeyDown(GLFW_KEY_ESCAPE)) {
            break;
        }

        // Update the game state.
        update(0.0f);

        lightManager.setViewPos(camera.getPosition());
        light4->setDirection(camera.getForward());
        light4->setPosition(camera.getPosition());

        i += 0.1f;

        // Render the game.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 model;

        //model = glm::scale(model, glm::vec3(10.0f, 0.1f, 10.0f));
        model = glm::rotate(model, glm::radians(i), glm::vec3(0.0f, 1.0f, 0.0f));

        test.bind();

        test.getShader().setUniform("projection", camera.getProjectionMatrix());
        test.getShader().setUniform("view", camera.getViewMatrix());
        test.getShader().setUniform("model", model);

        lightManager.bind(test.getShader());

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);

        window.display();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    return GL_TRUE;
}

GLvoid Game::update(GLfloat deltaTime) {
    if (Input::getInstance().isKeyDown(GLFW_KEY_W)) {
        camera.move(glm::vec3(0.0f, 0.0f, 0.05f));
    }
    else if (Input::getInstance().isKeyDown(GLFW_KEY_S)) {
        camera.move(glm::vec3(0.0f, 0.0f, -0.05f));
    }

    if (Input::getInstance().isKeyDown(GLFW_KEY_A)) {
        camera.move(glm::vec3(0.05f, 0.0f, 0.0f));
    }
    else if (Input::getInstance().isKeyDown(GLFW_KEY_D)) {
        camera.move(glm::vec3(-0.05f, 0.0f, 0.0f));
    }

    if (Input::getInstance().isKeyDown(GLFW_KEY_SPACE)) {
        camera.move(glm::vec3(0.0f, 0.05f, 0.0f));
    }

    camera.rotate(glm::vec2(Input::getInstance().getMouseDeltaX() * 0.05f,
                  Input::getInstance().getMouseDeltaY() * 0.05f));

    if (Input::getInstance().wasKeyPressed(GLFW_KEY_F)) {
        flashlightOn = !flashlightOn;
        std::cout << "Boop!" << std::endl;
    }
}

GLvoid Game::render() {
    /*
    */
}

Game::~Game() {
}