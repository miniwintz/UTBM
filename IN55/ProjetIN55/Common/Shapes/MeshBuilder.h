#ifndef MESHBUILDER_H
#define MESHBUILDER_H

#include "tiny_obj_loader.h"
#include "Object3D.h"
#include <assert.h>

class MeshBuilder : public Object3D
{
private:
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

public:
    MeshBuilder();
    MeshBuilder(std::vector<tinyobj::shape_t> shapes, std::vector<tinyobj::material_t> materials);
    virtual ~MeshBuilder();
    void log();

protected:
    void drawShape(const char* shader_name );
};

#endif // MESHBUILDER_H
