#include "texture2d.h"
#include <iostream>

Texture2D::Texture2D(const char *path, int forceChannels) {
    // Set the texture to be the default texture.
    textureID = 0;

    // Load the image data from a file.
    unsigned char *pixels = SOIL_load_image(path, &width, &height, &channels,
                                          forceChannels);

    // Error if the image failed to load.
    if (!pixels) {
        std::cerr << "Texture2D::Texture2D(" << path << ") failed to load: "
            << SOIL_last_result() << std::endl;
    }

    // Generate an OpenGL 2D texture with the given image data.
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, pixels);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    // Clear the image data.
    SOIL_free_image_data(pixels);
}

void Texture2D::bind(GLuint location) {
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