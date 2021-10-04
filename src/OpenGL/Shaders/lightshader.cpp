#include "lightshader.h"
#include <QDebug>

void LightShader::setupUniforms(){
    uniformLightColor=gl()->glGetUniformLocation(getShaderID(),"light.color");
    uniformAmbientIntensity=gl()->glGetUniformLocation(getShaderID(),"light.ambientIntensity");
    uniformDirection=gl()->glGetUniformLocation(getShaderID(),"light.direction");
    uniformDiffuseIntensity=gl()->glGetUniformLocation(getShaderID(),"light.diffuseIntensity");
    uniformModelColor=gl()->glGetUniformLocation(getShaderID(),"modelColor");
}

void LightShader::clearUniforms(){
    uniformLightColor=0;
    uniformAmbientIntensity=0;
    uniformDirection=0;
    uniformDiffuseIntensity=0;
}
