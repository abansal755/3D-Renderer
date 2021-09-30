#include "src/OpenGL/model.h"
#include "src/OpenGL/version.h"

class GridShader;

class GridModel:public Model{
    QColor color;
    GLint numLines;
    GLfloat sideLength;

    void initMesh();
protected:
    void populateUniforms();
public:
    GridModel(GLint numLines=20,GLfloat sideLength=5,
              QColor color=QColor(255,255,255),GridShader*shader=NULL);

    void setColor(QColor color){this->color=color;}
    QColor getColor(){return color;}
    void setNumLines(GLint numLines);
    GLint getNumLines(){return numLines;}
    void setSideLength(GLfloat sideLength);
    GLfloat getSideLength(){return sideLength;}
    void setGridConfig(GLint numLines,GLfloat sideLength);
};
