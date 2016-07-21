#include "window.h"
#include <iostream>

GLvoid Window::pollEvents() {
    glfwPollEvents();
}

GLvoid Window::display() {
    if (!window) {
        return;
    }

    glfwSwapBuffers(window);
}

GLvoid Window::center() {
    if (!window) {
        return;
    }

    const GLFWvidmode *videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    glfwSetWindowPos(window, (videoMode->width - width) / 2,
                     (videoMode->height - height) / 2);
}

GLvoid Window::setSize(int newWidth, int newHeight) {
    if (!window) {
        return;
    }

    width = newWidth;
    height = newHeight;

    glfwSetWindowSize(window, width, height);
}

GLboolean Window::open(const GLchar *newTitle, GLint newWidth, GLint newHeight,
GLboolean enableVSync) {
    width = newWidth;
    height = newHeight;
    title = newTitle;
    vSync = enableVSync;

    glewExperimental = GL_TRUE;

    // Initialize GLFW to create a window.
    if (!glfwInit()) {
        std::cerr << "Window::display() Failed to initialize GLFW!"
            << std::endl;

        return GL_FALSE;
    }

    // Set up properties for the window.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    // Create the actual window.
    window = glfwCreateWindow(width, height, title, NULL, NULL);

    if (!window) {
        std::cerr << "Window::display() failed to create window!" << std::endl;
        glfwTerminate();

        return GL_FALSE;
    }

    // Set the view port size.
    GLint viewWidth, viewHeight = 0;
    glfwGetFramebufferSize(window, &viewWidth, &viewHeight);

    glViewport(0, 0, viewWidth, viewHeight);

    // Set the OpenGL context to this window.
    glfwMakeContextCurrent(window);
    glfwFocusWindow(window);

    // Set the user pointer of GLFW window to this window object.
    glfwSetWindowUserPointer(window, this);

    // Enable V-Sync if desired.
    if (vSync) {
        glfwSwapInterval(1);
    }

    // Initialize GLEW()
    if (glewInit() != GLEW_OK) {
        std::cerr << "Window::display() failed to initialize GLEW!"
            << std::endl;

        glfwTerminate();

        return GL_FALSE;
    }

    return GL_TRUE;
}

GLboolean Window::isOpen() {
    if (window) {
        return !glfwWindowShouldClose(window);
    }

    return GL_FALSE;
}

GLint Window::getWidth() {
    return width;
}

GLint Window::getHeight() {
    return height;
}

GLFWwindow *Window::getGLFWWindow() {
    return window;
}

Window::~Window() {
    if (window) {
        glfwTerminate();
    }
}