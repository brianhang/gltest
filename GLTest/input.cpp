#include "input.h"

Input::Input() {
    firstPoll = true;

    for (int i = 0; i < INPUT_KEYS; i++) {
        keys[i] = 0;
    }

    for (int i = 0; i < INPUT_BUTTONS; i++) {
        buttons[i] = 0;
    }
}

Input &Input::getInstance() {
    static Input instance;

    return instance;
}

void Input::setWindow(GLFWwindow *newWindow) {
    window = newWindow;

    glfwSetKeyCallback(window, Input::handleInput);
    glfwSetMouseButtonCallback(window, Input::handleInput);
}

void Input::poll() {
    double newMouseX, newMouseY;

    glfwPollEvents();
    glfwGetCursorPos(window, &newMouseX, &newMouseY);

    if (firstPoll) {
        mouseX = newMouseX;
        mouseY = newMouseY;

        firstPoll = false;
    }

    mouseDeltaX = newMouseX - mouseX;
    mouseDeltaY = newMouseY - mouseY;

    mouseX = newMouseX;
    mouseY = newMouseY;
}

void Input::setMouseEnabled(bool enabled) {
    glfwSetInputMode(window, GLFW_CURSOR,
                     enabled ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
}

void Input::handleInput(GLFWwindow *window, int key, int scancode, int action,
int mods) {
    Input::getInstance().keys[key] = action;
}

void Input::handleInput(GLFWwindow *window, int button, int action, int mods) {
    Input::getInstance().buttons[button] = action;
}

bool Input::isKeyDown(int key) {
    return keys[key] > GLFW_RELEASE;
}

bool Input::isMouseDown(int button) {
    return buttons[button] > GLFW_RELEASE;
}

double Input::getMouseX() {
    return mouseX;
}

double Input::getMouseY() {
    return mouseY;
}

double Input::getMouseDeltaX() {
    return mouseDeltaX;
}

double Input::getMouseDeltaY() {
    return mouseDeltaY;
}