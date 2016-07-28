#pragma once

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "window.h"
#include "material.h"
#include "camera.h"
#include "input.h"
#include "lightmanager.h"
#include "model.h"

class Game {
private:
    Window window;
    Camera camera;
    LightManager lightManager;
    GLboolean flashlightOn;

public:
    Game();
    ~Game();
    GLvoid update(GLfloat deltaTime);
    GLvoid render();
    GLboolean initialize();
};