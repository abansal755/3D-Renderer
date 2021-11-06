#pragma once

#include <glm/glm.hpp>
#include <QOpenGLFunctions_3_3_Core>

class Vertex{
    glm::vec3 pos;
    glm::vec3 norm;
public:
    Vertex(glm::vec3 pos=glm::vec3(), glm::vec3 norm=glm::vec3())
        :pos(pos), norm(norm){}
    Vertex(GLfloat x,GLfloat y,GLfloat z,
           GLfloat nx,GLfloat ny,GLfloat nz)
        :pos(x,y,z), norm(nx,ny,nz){}

    void setPos(glm::vec3 pos){this->pos=pos;}
    glm::vec3 getPos(){return pos;}
    void setNorm(glm::vec3 norm){this->norm=norm;}
    glm::vec3 getNorm(){return norm;}
};
