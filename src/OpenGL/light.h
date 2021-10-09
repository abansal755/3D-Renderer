#pragma once

#include "lib/glm/glm.hpp"

#include <QOpenGLFunctions_3_3_Core>
#include <QColor>

class LightShader;

class Light: protected QOpenGLFunctions_3_3_Core{
    QColor color;
    GLfloat ambientIntensity;

    glm::vec3 direction;
    GLfloat diffuseIntensity;
public:
    Light(glm::vec3 direction=glm::vec3(0,-1,0), QColor color=QColor(255,255,255),
          GLfloat diffuseIntensity=1, GLfloat ambientIntensity=0.5);

    void useLight(LightShader*shader);

    void setColor(QColor color){this->color=color;}
    QColor getColor(){return color;}
    void setAmbientIntensity(GLfloat ambientIntensity){this->ambientIntensity=ambientIntensity;}
    void setDirection(glm::vec3 direction){this->direction=-direction;}
    glm::vec3 getDirection(){return direction;}
    void setDiffuseIntensity(GLfloat diffuseIntensity){this->diffuseIntensity=diffuseIntensity;}
    GLfloat getDiffuseIntensity(){return diffuseIntensity;}
};
