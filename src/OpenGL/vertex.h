#pragma once

#include "lib/glm/glm.hpp"
#include <QOpenGLFunctions_3_3_Core>

class Vertex{
    glm::vec3 pos;
    glm::vec3 norm;
    glm::vec2 uv;
public:
    Vertex(glm::vec3 pos=glm::vec3(), glm::vec3 norm=glm::vec3(),
           glm::vec2 uv=glm::vec2())
        :pos(pos), norm(norm), uv(uv){}
    Vertex(GLfloat x,GLfloat y,GLfloat z,
           GLfloat nx,GLfloat ny,GLfloat nz,
           GLfloat u,GLfloat v)
        :pos(x,y,z), norm(nx,ny,nz), uv(u,v){}

    void setPos(glm::vec3 pos){this->pos=pos;}
    glm::vec3 getPos(){return pos;}
    void setNorm(glm::vec3 norm){this->norm=norm;}
    glm::vec3 getNorm(){return norm;}
    void setUV(glm::vec2 uv){this->uv=uv;}
    glm::vec2 getUV(){return uv;}
};
