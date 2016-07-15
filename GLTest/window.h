#pragma once

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <iostream>

class Window {
    GLFWwindow *window;
    int width;
    int height;
    const char *title;
    bool vSync;

public:
    Window(const char *newTitle, int newWidth, int newHeight,
           bool enableVSync = true);
    ~Window();
    bool open();
    bool isOpen();
    void display();
    void pollEvents();
    void center();
};