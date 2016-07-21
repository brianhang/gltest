#include "input.h"

Input::Input() {
    firstPoll = GL_TRUE;

    for (GLint i = 0; i < INPUT_KEYS; i++) {
        keys[i] = 0;
    }

    for (GLint i = 0; i < INPUT_BUTTONS; i++) {
        buttons[i] = 0;
    }
}

Input &Input::getInstance() {
    static Input instance;

    return instance;
}

GLvoid Input::setWindow(GLFWwindow *newWindow) {
    window = newWindow;

    glfwSetKeyCallback(window, Input::handleInput);
    glfwSetMouseButtonCallback(window, Input::handleInput);
}

GLvoid Input::poll() {
    GLdouble newMouseX, newMouseY;

    glfwPollEvents();
    glfwGetCursorPos(window, &newMouseX, &newMouseY);

    if (firstPoll) {
        mouseX = newMouseX;
        mouseY = newMouseY;

        firstPoll = GL_FALSE;
    }

    mouseDeltaX = newMouseX - mouseX;
    mouseDeltaY = newMouseY - mouseY;

    mouseX = newMouseX;
    mouseY = newMouseY;
}

GLvoid Input::setMouseEnabled(GLboolean enabled) {
    glfwSetInputMode(window, GLFW_CURSOR,
                     enabled ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
}

GLvoid Input::handleInput(GLFWwindow *window, GLint key, GLint scancode,
GLint action, GLint mods) {
    Input::getInstance().keys[key] = action;
}

GLvoid Input::handleInput(GLFWwindow *window, int button, int action,
int mods) {
    Input::getInstance().buttons[button] = action;
}

GLboolean Input::isKeyDown(GLint key) {
    return keys[key] > GLFW_RELEASE;
}

GLboolean Input::wasKeyPressed(GLint key) {
    return keys[key] == GLFW_PRESS;
}

GLboolean Input::wasKeyReleased(GLint key) {
    return keys[key] == GLFW_RELEASE;
}

GLboolean Input::isMouseDown(GLint button) {
    return buttons[button] > GLFW_RELEASE;
}

GLdouble Input::getMouseX() {
    return mouseX;
}

GLdouble Input::getMouseY() {
    return mouseY;
}

GLdouble Input::getMouseDeltaX() {
    return mouseDeltaX;
}

GLdouble Input::getMouseDeltaY() {
    return mouseDeltaY;
}