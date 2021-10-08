#pragma once

#include "mesh.h"
#include "material.h"

#include <QOpenGLFunctions_3_3_Core>

class Model: protected QOpenGLFunctions_3_3_Core{
    Mesh*mesh;
    Material*mat;
    glm::mat4 modelMatrix;
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
};
