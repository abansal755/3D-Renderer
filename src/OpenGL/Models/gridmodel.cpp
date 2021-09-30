#include "gridmodel.h"
#include "src/OpenGL/mesh.h"
#include "src/OpenGL/Shaders/gridshader.h"

GridModel::GridModel(GLint numLines,GLfloat sideLength,
          QColor color,GridShader*shader)
    :Model(NULL,glm::mat4(1),(Shader*)shader),numLines(numLines),
      sideLength(sideLength),color(color)
{
    initMesh();
}

void GridModel::initMesh(){
    if(mesh) delete mesh;

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    /*
     * gap=sideLength/numLines
     * -sideLength/2 to sideLength/2=x
     * -x,-x+gap,-x+2*gap,....x-gap,x
    */

    GLfloat gap=sideLength/(numLines-1);
    for(int i=0;i<numLines;i++)
        vertices.push_back(Vertex(-sideLength/2+i*gap,0,sideLength/2,0,0,0));
    for(int i=0;i<numLines;i++)
        vertices.push_back(Vertex(-sideLength/2+i*gap,0,-sideLength/2,0,0,0));
    for(int i=0;i<numLines;i++){
        indices.push_back(i);
        indices.push_back(i+numLines);
    }
    indices.push_back(0);
    indices.push_back(numLines-1);
    indices.push_back(numLines);
    indices.push_back(2*numLines-1);
    for(int i=0;i<numLines-2;i++)
        vertices.push_back(Vertex(sideLength/2,0,sideLength/2-(i+1)*gap,0,0,0));
    for(int i=0;i<numLines-2;i++)
        vertices.push_back(Vertex(-sideLength/2,0,sideLength/2-(i+1)*gap,0,0,0));
    for(int i=2*numLines;i<=3*numLines-3;i++){
        indices.push_back(i);
        indices.push_back(i+numLines-2);
    }

    mesh=new Mesh(vertices,indices,GL_STATIC_DRAW,GL_LINES);
}

void GridModel::populateUniforms(){
    GridShader*shader=(GridShader*)getShader();
    GLuint uniformModelColor=shader->getModelColorLocation();
    gl()->glUniform4f(uniformModelColor,color.redF(),color.greenF(),color.blueF(),color.alphaF());
}
