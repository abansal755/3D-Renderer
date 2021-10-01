#include "src/OpenGL/model.h"
#include <QColor>

class LightShader;

class ColorModel : public Model{
    QColor color;
protected:
    virtual void populateUniforms();
public:
    ColorModel(Mesh*mesh=NULL,QColor color=QColor(128,128,128),
              glm::mat4 model=glm::mat4(1),LightShader*shader=NULL)
        :Model(mesh,model,(Shader*)shader),color(color){}

    void setColor(QColor color){this->color=color;}
    QColor getColor(){return color;}
};
