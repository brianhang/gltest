#include "texture2d.h"
#include <iostream>

Texture2D::Texture2D(const std::string &path, GLint format) {
    // Set the texture to be the default texture.
    textureID = 0;

    // Load the image data from a file.
    GLubyte *pixels = SOIL_load_image(path.c_str(), &width, &height, &channels,
                                      SOIL_LOAD_RGB);

    // Error if the image failed to load.
    if (!pixels) {
        std::cerr << "Texture2D::Texture2D(" << path << ") failed to load: "
                  << SOIL_last_result() << std::endl;
    }

    // Generate an OpenGL 2D texture with the given image data.
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
                 GL_UNSIGNED_BYTE, pixels);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    // Clear the image data.
    SOIL_free_image_data(pixels);
}

GLvoid Texture2D::bind(GLuint location) {
    glActiveTexture(GL_TEXTURE0 + location);
    glBindTexture(GL_TEXTURE_2D, textureID);
}

GLuint Texture2D::getID() {
    return textureID;
}

Texture2D::~Texture2D() {
    if (textureID) {
        glDeleteTextures(1, &textureID);
    }
}