#pragma once

#include "lib/glm/glm.hpp"

#include <QOpenGLFunctions_3_3_Core>
#include <QColor>

class Light{
    QColor color;
    GLfloat ambientIntensity;
public:
    Light(QColor color=QColor(255,255,255),
          GLfloat ambientIntensity=0.5)
        :color(color),ambientIntensity(ambientIntensity){}

    void setColor(QColor color){this->color=color;}
    QColor getColor(){return color;}
    void setAmbientIntensity(GLfloat ambientIntensity){this->ambientIntensity=ambientIntensity;}
    GLfloat getAmbientIntensity(){return ambientIntensity;}
};
