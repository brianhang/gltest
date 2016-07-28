#include "mesh.h"

Mesh::Mesh(std::vector<GLuint> newIndices, std::vector<Vertex> newVertices,
std::vector<Texture> newTextures) {
    indices = newIndices;
    vertices = newVertices;
    textures = newTextures;

    setup();
}

GLvoid Mesh::setup() {
    // Create needed buffers.
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Create the vertex array for this mesh.
    glGenVertexArrays(1, &VAO);

    // Load the buffers into the vertex array.
    glBindVertexArray(VAO);

    // Set up the vertex buffer.
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex),
                 &vertices[0], GL_STATIC_DRAW);

    // Set up the element buffer.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
                 &indices[0], GL_STATIC_DRAW);

    // Position attribute.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (GLvoid*) 0);
    glEnableVertexAttribArray(0);

    // Normal attribute.
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (GLvoid*) offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);

    // Texture coordinates.
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (GLvoid*)offsetof(Vertex, texCoord));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

GLvoid Mesh::draw(Shader &shader) {
    GLuint diffuseIndex = 0;
    GLuint specularIndex = 0;

    // Set all of the textures for the mesh.
    for (GLuint i = 0; i < textures.size(); i++) {
        std::string name;

        switch (textures[i].type) {
            case DIFFUSE:
                name = "diffuse" + diffuseIndex;
                diffuseIndex++;
            case SPECULAR:
                name = "specular" + specularIndex;
                specularIndex++;
            default:
                name = "unknown";
        }

        shader.setUniform(name.c_str(), i);

        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }

    // Draw the actual mesh.
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, vertices.size(), GL_UNSIGNED_INT, NULL);
    glBindVertexArray(0);
}