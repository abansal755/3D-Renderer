#pragma once

#include "mesh.h"
#include "material.h"
#include "camera.h"
#include "Lights/directionallight.h"

#include <QOpenGLFunctions_3_3_Core>
#include <vector>

class Model: protected QOpenGLFunctions_3_3_Core{
    Mesh*mesh;
    Material*mat;
    glm::mat4 modelMatrix;

    inline static Camera* camera=NULL;
    inline static std::vector<DirectionalLight*> directionalLights;
public:
    Model(Mesh*mesh=NULL,Material*mat=NULL,
          glm::mat4 modelMatrix=glm::mat4(1));

    void renderModel();

    Mesh* getMesh(){return mesh;}
    void setMesh(Mesh*mesh){this->mesh=mesh;}
    Material* getMaterial(){return mat;}
    void setMaterial(Material*mat){this->mat=mat;}
    glm::mat4 getModelMatrix(){return modelMatrix;}
    void setModelMatrix(glm::mat4 modelMatrix){this->modelMatrix=modelMatrix;}

    static Camera* getCamera(){return camera;}
    static void setCamera(Camera*camera){Model::camera=camera;}
    static void addDirectionalLight(DirectionalLight*light){
        Model::directionalLights.push_back(light);
    }
    static void removeDirectionalLight(DirectionalLight*light);
};
