#include "src/OpenGL/version.h"
#include "lib/glm/glm.hpp"

class Vertex{
    glm::vec3 pos;
    glm::vec2 texCoord;
public:
    Vertex(glm::vec3 pos=glm::vec3(), glm::vec2 texCoord=glm::vec2())
        :pos(pos), texCoord(texCoord){}
    Vertex(GLfloat x,GLfloat y,GLfloat z,
           GLfloat u,GLfloat v)
        :pos(x,y,z), texCoord(u,v){}

    void setPos(glm::vec3 pos){this->pos=pos;}
    glm::vec3 getPos(){return pos;}
    void setTexCoord(glm::vec2 texCoord){this->texCoord=texCoord;}
    glm::vec2 getTexCoord(){return texCoord;}
};
