#include "window.h"

Window::Window(const char *newTitle, int newWidth, int newHeight,
               bool enableVSync) {
    width = newWidth;
    height = newHeight;
    title = newTitle;
    vSync = enableVSync;
}

bool Window::open() {
    glewExperimental = GL_TRUE;

    // Initialize GLFW to create a window.
    if (!glfwInit()) {
        std::cerr << "Window::display() Failed to initialize GLFW!"
                  << std::endl;

        return false;
    }

    // Set up properties for the window.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create the actual window.
    window = glfwCreateWindow(width, height, title, NULL, NULL);

    if (!window) {
        std::cerr << "Window::display() failed to create window!" << std::endl;
        glfwTerminate();

        return false;
    }

    // Set the view port size.
    int viewWidth, viewHeight = 0;
    glfwGetFramebufferSize(window, &viewWidth, &viewHeight);

    glViewport(0, 0, viewWidth, viewHeight);

    // Set the OpenGL context to this window.
    glfwMakeContextCurrent(window);

    // Enable V-Sync if desired.
    if (vSync) {
        glfwSwapInterval(1);
    }

    // Initialize GLEW()
    if (glewInit() != GLEW_OK) {
        std::cerr << "Window::display() failed to initialize GLEW!"
                  << std::endl;

        glfwTerminate();

        return false;
    }

    return true;
}

bool Window::isOpen() {
    if (window) {
        return !glfwWindowShouldClose(window);
    }

    return false;
}

void Window::pollEvents() {
    glfwPollEvents();
}

void Window::display() {
    if (window) {
        glfwSwapBuffers(window);
    }
}

void Window::center() {
    if (!window) {
        return;
    }

    const GLFWvidmode *videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    glfwSetWindowPos(window, (videoMode->width - width) / 2,
        (videoMode->height - height) / 2);
}

Window::~Window() {
    if (window) {
        glfwTerminate();
    }
}