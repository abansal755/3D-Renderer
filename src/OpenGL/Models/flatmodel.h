#include "src/OpenGL/model.h"
#include <QColor>

class FlatShader;

class FlatModel : public Model{
    QColor color;
protected:
    virtual void populateUniforms();
public:
    FlatModel(Mesh*mesh=NULL,QColor color=QColor(128,128,128),
              glm::mat4 model=glm::mat4(1),FlatShader*shader=NULL)
        :Model(mesh,model,(Shader*)shader),color(color){}

    void setColor(QColor color){this->color=color;}
    QColor getColor(){return color;}
};
