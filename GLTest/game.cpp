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
    Model thing("models/nanosuit/nanosuit.obj");
    Shader test("default", "default");

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
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 model;

        //model = glm::scale(model, glm::vec3(10.0f, 0.1f, 10.0f));
        model = glm::rotate(model, glm::radians(i), glm::vec3(0.0f, 1.0f, 0.0f));
        //model = glm::scale(model, glm::vec3(0.2f, 0.05f, 0.2f));

        test.bind();

        test.setUniform("projection", camera.getProjectionMatrix());
        test.setUniform("view", camera.getViewMatrix());
        test.setUniform("model", model);

        lightManager.bind(test);

        thing.draw(test);

        window.display();
    }

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