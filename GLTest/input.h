#pragma once

#include <GLFW/glfw3.h>

#define INPUT_KEYS 512
#define INPUT_BUTTONS 16

class Input {
private:
    GLboolean firstPoll;
    GLint keys[INPUT_KEYS];
    GLint buttons[INPUT_BUTTONS];
    GLFWwindow *window;
    GLdouble mouseX;
    GLdouble mouseY;
    GLdouble mouseDeltaX;
    GLdouble mouseDeltaY;

protected:
    Input();

public:
    static void handleInput(GLFWwindow *window, GLint key, GLint scancode,
                            GLint action, GLint mods);
    static void handleInput(GLFWwindow *window, GLint button, GLint action,
                            GLint mods);
    GLvoid poll();
    GLvoid setMouseEnabled(GLboolean enabled);
    GLvoid setWindow(GLFWwindow *newWindow);
    GLboolean isKeyDown(GLint key);
    GLboolean wasKeyPressed(GLint key);
    GLboolean wasKeyReleased(GLint key);
    GLboolean isMouseDown(GLint button);
    static Input &getInstance();
    GLdouble getMouseX();
    GLdouble getMouseY();
    GLdouble getMouseDeltaX();
    GLdouble getMouseDeltaY();
};

