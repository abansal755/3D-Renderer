#include "simplevertex.h"

class Vertex:public SimpleVertex{
    glm::vec3 norm;
public:
    Vertex(glm::vec3 pos=glm::vec3(), glm::vec3 norm=glm::vec3())
        :SimpleVertex(pos), norm(norm){}
    Vertex(GLfloat x,GLfloat y,GLfloat z,
           GLfloat nx,GLfloat ny,GLfloat nz)
        :SimpleVertex(x,y,z), norm(nx,ny,nz){}

    void setNorm(glm::vec3 norm){this->norm=norm;}
    glm::vec3 getNorm(){return norm;}
};
