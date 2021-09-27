#include "simplevertex.h"

class Vertex:public SimpleVertex{
    glm::vec2 texCoord;
public:
    Vertex(glm::vec3 pos=glm::vec3(), glm::vec2 texCoord=glm::vec2())
        :SimpleVertex(pos), texCoord(texCoord){}
    Vertex(GLfloat x,GLfloat y,GLfloat z,
           GLfloat u,GLfloat v)
        :SimpleVertex(x,y,z), texCoord(u,v){}

    void setTexCoord(glm::vec2 texCoord){this->texCoord=texCoord;}
    glm::vec2 getTexCoord(){return texCoord;}
};
