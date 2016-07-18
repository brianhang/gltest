#pragma once

#include <GLFW/glfw3.h>

#define INPUT_KEYS 512
#define INPUT_BUTTONS 16

class Input {
private:
    bool firstPoll;
    int keys[INPUT_KEYS];
    int buttons[INPUT_BUTTONS];
    GLFWwindow *window;
    double mouseX;
    double mouseY;
    double mouseDeltaX;
    double mouseDeltaY;

protected:
    Input();

public:
    static void handleInput(GLFWwindow *window, int key, int scancode,
                            int action, int mods);
    static void handleInput(GLFWwindow *window, int button, int action,
                            int mods);
    void poll();
    void setMouseEnabled(bool enabled);
    void setWindow(GLFWwindow *newWindow);
    bool isKeyDown(int key);
    bool isMouseDown(int button);
    static Input &getInstance();
    double getMouseX();
    double getMouseY();
    double getMouseDeltaX();
    double getMouseDeltaY();
};

