#include "lightshader.h"
#include <QDebug>

void LightShader::setupUniforms(){
    uniformLightColor=glGetUniformLocation(getShaderID(),"light.color");
    uniformAmbientIntensity=glGetUniformLocation(getShaderID(),"light.ambientIntensity");
    uniformDirection=glGetUniformLocation(getShaderID(),"light.direction");
    uniformDiffuseIntensity=glGetUniformLocation(getShaderID(),"light.diffuseIntensity");
    uniformModelColor=glGetUniformLocation(getShaderID(),"modelColor");
}

void LightShader::clearUniforms(){
    uniformLightColor=0;
    uniformAmbientIntensity=0;
    uniformDirection=0;
    uniformDiffuseIntensity=0;
}
