#pragma once

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include "window.h"
#include "shader.h"
#include "texture2d.h"
#include "camera.h"
#include "input.h"
#include "lightmanager.h"

class Game {
private:
    Window window;
    Camera camera;
    LightManager lightManager;

public:
    Game();
    ~Game();
    void update(float deltaTime);
    void render();
    bool initialize();
};