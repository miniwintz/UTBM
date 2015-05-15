#ifndef MESHBUILDER_H
#define MESHBUILDER_H

#include "tiny_obj_loader.h"
#include "Object3D.h"
#include <assert.h>
#include <assimp/scene.h>           // Output data structure

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

class MeshBuilder : public Object3D
{
private:
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    aiMesh** meshes;
    aiAnimation** animations;
    aiLight** lights;
    aiMaterial** assimpMaterials;
    aiCamera** cameras;

public:
    MeshBuilder();
    MeshBuilder(std::vector<tinyobj::shape_t> shapes, std::vector<tinyobj::material_t> materials);
    MeshBuilder(const aiScene* scene);
    virtual ~MeshBuilder();
    void buildMeshWithTinyObjLoader();
    void buildMeshWithAssimp();
    void log();

protected:
    void drawShape(const char* shader_name );
};

#endif // MESHBUILDER_H
