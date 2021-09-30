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
    GridModel(GLint numLines=10,GLfloat sideLength=5,\
              QColor color=QColor(255,255,255),GridShader*shader=NULL);
};
