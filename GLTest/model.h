#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <unordered_map>
#include "mesh.h"

typedef std::unordered_map<std::string, Texture> TextureCache;

class Model {
private:
    GLvoid load();
    GLvoid loadNode(aiNode *node, const aiScene *scene,
                    TextureCache &textureCache);
    Mesh loadMesh(aiMesh *mesh, const aiScene *scene,
                  TextureCache &textureCache);
    std::vector<Texture> loadTextures(aiMaterial *material, aiTextureType type,
                                      TextureType realType,
                                      const std::string &directory,
                                      TextureCache &textureCache);
    std::string path;
    std::vector<Mesh> meshes;

public:
    Model(std::string newPath);
    GLvoid draw(Shader &shader);
    std::string getModel();
};

