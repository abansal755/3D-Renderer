#include "lib/glm/glm.hpp"

#include <QColor>

class Mesh;
class Shader;
class Camera;

class Model{
    Mesh*mesh;
    glm::mat4 model;
    QColor color;
    Shader*shader;
public:
    Model(Mesh*mesh=NULL,QColor color=QColor(128,128,128),
          glm::mat4 model=glm::mat4(1),Shader*shader=NULL)
        :mesh(mesh),model(model),color(color),shader(shader){}

    void setMesh(Mesh*mesh){this->mesh=mesh;}
    Mesh* getMesh(){return mesh;}
    void setModelMatrix(glm::mat4 model){this->model=model;}
    glm::mat4 getModelMatrix(){return model;}
    void setColor(QColor color){this->color=color;}
    QColor getColor(){return color;}
    void setShader(Shader*shader){this->shader=shader;}
    Shader* getShader(){return shader;}

    void renderModel(Camera*camera);
};
