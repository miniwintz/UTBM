#include "MeshBuilder.h"

using namespace std;

MeshBuilder::MeshBuilder()
{

}

MeshBuilder::MeshBuilder(std::vector<tinyobj::shape_t> shapes, std::vector<tinyobj::material_t> materials)
{
    this->shapes = shapes;
    this->materials = materials;
}

MeshBuilder::MeshBuilder(const aiScene* scene)
{
    this->meshes = scene->mMeshes;
    this->assimpMaterials = scene->mMaterials;
    this->cameras = scene->mCameras;
    this->lights = scene->mLights;
    this->animations = scene->mAnimations;

    cout << scene->HasAnimations() << endl;

}

MeshBuilder::~MeshBuilder()
{

}


void MeshBuilder::drawShape(const char* shader_name )
{
   buildMeshWithTinyObjLoader();
    //buildMeshWithAssimp();
}

void MeshBuilder::buildMeshWithTinyObjLoader()
{
    for (size_t i = 0; i < shapes.size(); i++)
    {
        GLint var1 = glGetAttribLocation( m_Framework->getCurrentShaderId(), "position" );
        glEnableVertexAttribArray( var1 );
        glVertexAttribPointer( var1, 3, GL_FLOAT, GL_FALSE, 0, &this->shapes[i].mesh.positions[0] );

//      GLint var2 = glGetAttribLocation( m_Framework->getCurrentShaderId(), "color" );
//        glEnableVertexAttribArray( var2 );
//        glVertexAttribPointer( var2, 3, GL_FLOAT, GL_FALSE, 0, g_TabColors );

        glDrawElements(GL_TRIANGLES, this->shapes[i].mesh.indices.size(), GL_UNSIGNED_INT, &this->shapes[i].mesh.indices[0]);

        glDisableVertexAttribArray( var1 );
       // glDisableVertexAttribArray( var2 );
    }
}

void MeshBuilder::buildMeshWithAssimp()
{
cout << this->meshes[0]->mNumVertices << endl;

//   for(int i =0;i< this->meshes[0]->mNumVertices;i++)
//   {
//       cout << i << endl;
//   }
}

void MeshBuilder::log()
{
    for (size_t i = 0; i < shapes.size(); i++)
    {
      printf("shape[%ld].name = %s\n", i, shapes[i].name.c_str());
      printf("Size of shape[%ld].indices: %ld\n", i, shapes[i].mesh.indices.size());
      printf("Size of shape[%ld].material_ids: %ld\n", i, shapes[i].mesh.material_ids.size());
      assert((shapes[i].mesh.indices.size() % 3) == 0);

      for (size_t f = 0; f < shapes[i].mesh.indices.size() / 3; f++)
      {
        printf("  idx[%ld] = %d, %d, %d. mat_id = %d\n", f, shapes[i].mesh.indices[3*f+0], shapes[i].mesh.indices[3*f+1], shapes[i].mesh.indices[3*f+2], shapes[i].mesh.material_ids[f]);

      }

      printf("shape[%ld].vertices: %ld\n", i, shapes[i].mesh.positions.size());
      assert((shapes[i].mesh.positions.size() % 3) == 0);
      for (size_t v = 0; v < shapes[i].mesh.positions.size() / 3; v++)
      {
        printf("  v[%ld] = (%f, %f, %f)\n", v,shapes[i].mesh.positions[3*v+0],shapes[i].mesh.positions[3*v+1],shapes[i].mesh.positions[3*v+2]);
      }
    }
}

