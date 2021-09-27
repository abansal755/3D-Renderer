#include "version.h"
#include "lib/glm/glm.hpp"

class SimpleVertex{
    glm::vec3 pos;
public:
    SimpleVertex(glm::vec3 pos=glm::vec3()):pos(pos){}
    SimpleVertex(GLfloat x,GLfloat y,GLfloat z):pos(x,y,z){}

    void setPos(glm::vec3 pos){this->pos=pos;}
    glm::vec3 getPos(){return pos;}
};
