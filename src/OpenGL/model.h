#pragma once

#include <glm/glm.hpp>

#include <QOpenGLFunctions_3_3_Core>
#include <QColor>

class Mesh;
class Shader;
class Camera;

class Model: protected QOpenGLFunctions_3_3_Core{
    glm::mat4 model;
    Mesh*mesh;
    Shader*shader;
protected:
    virtual void populateUniforms(){}
public:
    Model(Mesh*mesh=NULL,glm::mat4 model=glm::mat4(1),Shader*shader=NULL);

    void setMesh(Mesh*mesh){this->mesh=mesh;}
    Mesh* getMesh(){return mesh;}
    void setModelMatrix(glm::mat4 model){this->model=model;}
    glm::mat4 getModelMatrix(){return model;}
    void setShader(Shader*shader){this->shader=shader;}
    Shader* getShader(){return shader;}

    void renderModel(Camera*camera);
};
