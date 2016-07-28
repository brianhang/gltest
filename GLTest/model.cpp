#include <iostream>
#include "model.h"

static GLuint getTextureID(std::string path) {
    // Set the texture to be the default texture.
    GLuint textureID = 0;
    GLint width, height, channels;

    // Load the image data from a file.
    GLubyte *pixels = SOIL_load_image(path.c_str(), &width, &height, &channels,
                                      SOIL_LOAD_RGB);

    // Error if the image failed to load.
    if (!pixels) {
        std::cerr << "getTextureID(" << path << ") failed to load: "
                  << SOIL_last_result() << std::endl;

        return 0;
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

    return textureID;
}

Model::Model(std::string newPath) {
    path = newPath;
    load();
}

GLvoid Model::load() {
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate
                                             | aiProcess_FlipUVs);
    TextureCache textureCache;

    if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE
        || !scene->mRootNode) {
        std::cerr << "Model::load(" << path << ") failed to load scene! "
                  << importer.GetErrorString() << std::endl;

        return;
    }

    loadNode(scene->mRootNode, scene, textureCache);
}

GLvoid Model::loadNode(aiNode *node, const aiScene *scene,
TextureCache &textureCache) {
    GLuint i;

    // Convert Assimp meshes into our mesh format.
    for (i = 0; i < node->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[i];

        meshes.push_back(loadMesh(mesh, scene, textureCache));
    }

    // Recursively load child meshes.
    for (i = 0; i < node->mNumChildren; i++) {
        loadNode(node->mChildren[i], scene, textureCache);
    }
}

Mesh Model::loadMesh(aiMesh *mesh, const aiScene *scene,
TextureCache &textureCache) {
    std::vector<GLuint> indices;
    std::vector<Vertex> vertices;
    std::vector<Texture> textures;
    GLuint i;

    for (i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;

        vertex.position.x = mesh->mVertices[i].x;
        vertex.position.y = mesh->mVertices[i].y;
        vertex.position.z = mesh->mVertices[i].z;
        
        vertex.normal.x = mesh->mNormals[i].x;
        vertex.normal.y = mesh->mNormals[i].y;
        vertex.normal.z = mesh->mNormals[i].z;

        if (mesh->mTextureCoords[0]) {
            vertex.texCoord.x = mesh->mTextureCoords[0][i].x;
            vertex.texCoord.y = mesh->mTextureCoords[0][i].y;
        } else {
            vertex.texCoord.x = 0.0f;
            vertex.texCoord.y = 0.0f;
        }

        vertices.push_back(vertex);
    }

    for (i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];

        for (GLuint j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    if (mesh->mMaterialIndex >= 0) {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

        // Base directory for the model's textures.
        std::string directory = path.substr(0, path.find_last_of("/") + 1);

        // Insert diffuse textures.
        std::vector <Texture> diffuse = loadTextures(material,
                                                     aiTextureType_DIFFUSE,
                                                     DIFFUSE,
                                                     directory,
                                                     textureCache);
        textures.insert(textures.end(), diffuse.begin(), diffuse.end());

        // Insert specular textures.
        std::vector <Texture> specular = loadTextures(material,
                                                      aiTextureType_SPECULAR,
                                                      SPECULAR,
                                                      directory,
                                                      textureCache);
        textures.insert(textures.end(), specular.begin(), specular.end());

        // Insert normal textures.
        std::vector <Texture> normal = loadTextures(material,
                                                    aiTextureType_NORMALS,
                                                    NORMAL,
                                                    directory,
                                                    textureCache);
        textures.insert(textures.end(), normal.begin(), normal.end());
    }

    return Mesh(indices, vertices, textures);
}

std::vector<Texture> Model::loadTextures(aiMaterial *material,
aiTextureType type, TextureType realType, const std::string &directory,
TextureCache &textureCache) {
    std::vector<Texture> textures;

    for (GLuint i = 0; i < material->GetTextureCount(type); i++) {
        aiString path;
        std::string fullPath;
        material->GetTexture(type, i, &path);

        fullPath = directory + path.C_Str();

        // Try to load the texture from cache.
        TextureCache::const_iterator result = textureCache.find(fullPath);

        if (result != textureCache.end()) {
            textures.push_back(result->second);

            continue;
        }

        // Not in cache, so load it and add it to the cache.
        Texture texture;
        texture.id = getTextureID(fullPath);
        texture.type = realType;

        textureCache[fullPath] = texture;

        textures.push_back(texture);
    }

    return textures;
}

GLvoid Model::draw(Shader &shader) {
    for (GLuint i = 0; i < meshes.size(); i++) {
        meshes[i].draw(shader);
    }
}

std::string Model::getModel() {
    return path;
}