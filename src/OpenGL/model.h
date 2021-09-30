#include "lib/glm/glm.hpp"

#include <QColor>

class Mesh;
class Shader;
class Camera;

class Model{
    glm::mat4 model;
    Shader*shader;
protected:
    Mesh*mesh;
    virtual void populateUniforms(){}
public:
    Model(Mesh*mesh=NULL,glm::mat4 model=glm::mat4(1),Shader*shader=NULL)
        :mesh(mesh),model(model),shader(shader){}

    void setMesh(Mesh*mesh){this->mesh=mesh;}
    Mesh* getMesh(){return mesh;}
    void setModelMatrix(glm::mat4 model){this->model=model;}
    glm::mat4 getModelMatrix(){return model;}
    void setShader(Shader*shader){this->shader=shader;}
    Shader* getShader(){return shader;}

    void renderModel(Camera*camera);
};
