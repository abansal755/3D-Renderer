#include "version.h"
#include <vector>

class Mesh{
    GLsizei numIndices=0,numVertices=0;
    GLuint VAO=0,VBO=0,IBO=0;

    Mesh(const Mesh& mesh);
    Mesh operator=(const Mesh& mesh);
public:
    Mesh() {};
    Mesh(std::vector<GLfloat>& vertices, std::vector<unsigned int>& indices);
    ~Mesh();

    void createMesh(std::vector<GLfloat>& vertices, std::vector<unsigned int>& indices);
    void clearMesh();
    void renderMesh();//mesh must not be empty before calling
    bool empty() { return (VAO == 0); }
};
