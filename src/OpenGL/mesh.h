#include "version.h"
#include "vertex.h"
#include <vector>

class Mesh{
    GLsizei numIndices=0,numVertices=0;
    GLuint VAO=0,VBO=0,IBO=0;

    GLenum usageMode,drawMode;

    Mesh(const Mesh& mesh);
    Mesh operator=(const Mesh& mesh);
protected:
    virtual void describeData(std::vector<Vertex>& vertices);
public:
    Mesh() {};
    Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices,
         GLenum usageMode=GL_STATIC_DRAW, GLenum drawMode=GL_TRIANGLES);
    virtual ~Mesh();

    void createMesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);
    void clearMesh();
    void renderMesh();//mesh must not be empty before calling
    bool empty() { return (VAO == 0); }

    void setUsageMode(GLenum usageMode){this->usageMode=usageMode;}
    GLenum getUsageMode(){return usageMode;}
    void setDrawMode(GLenum drawMode){this->drawMode=drawMode;}
    GLenum getDrawMode(){return drawMode;}

    //Only use these functions for dynamic buffers
    void updateVertexBuffer(std::vector<Vertex>&vertices,GLintptr offset=0);
    void updateIndexBuffer(std::vector<unsigned int>&indices,GLintptr offset=0);
};
