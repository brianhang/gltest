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
    ~Window();
    void display();
    void pollEvents();
    void center();
    void setSize(int width, int height);
    bool open(const char *newTitle, int newWidth, int newHeight,
              bool enableVSync);
    bool isOpen();
    int getWidth();
    int getHeight();
    GLFWwindow *getGLFWWindow();
};