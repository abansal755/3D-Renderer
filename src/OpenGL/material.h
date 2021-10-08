#pragma once

#include "texture.h"
#include "Shaders/lightshader.h"

#include <QColor>

class Material{
    QColor color=QColor(Qt::gray);
    Texture* tex=NULL;
    bool isTex=false;
    LightShader* shader;
public:
    Material(LightShader*shader=NULL):shader(shader){}

    QColor getColor(){return color;}
    void setColor(QColor color){this->color=color;}
    Texture* getTexture(){return tex;}
    void setTexture(Texture*tex){this->tex=tex;}
    bool isTextureUsed(){return isTex;}
    void setIsTextureUsed(bool isTex){this->isTex=isTex;}
    LightShader* getShader(){return shader;}
    void setShader(LightShader*shader){this->shader=shader;}
};
