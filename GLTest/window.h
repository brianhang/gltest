#pragma once

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window {
    GLFWwindow *window;
    GLint width;
    GLint height;
    const GLchar *title;
    GLboolean vSync;

public:
    ~Window();
    GLvoid display();
    GLvoid pollEvents();
    GLvoid center();
    GLvoid setSize(GLint width, GLint height);
    GLboolean open(const GLchar *newTitle, GLint newWidth, GLint newHeight,
                   GLboolean enableVSync);
    GLboolean isOpen();
    GLint getWidth();
    GLint getHeight();
    GLFWwindow *getGLFWWindow();
};