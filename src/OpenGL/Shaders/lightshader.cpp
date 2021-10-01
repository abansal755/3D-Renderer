#include "lightshader.h"
#include <QDebug>

void LightShader::setupUniforms(){
    uniformLightColor=gl()->glGetUniformLocation(program,"light.color");
    uniformAmbientIntensity=gl()->glGetUniformLocation(program,"light.ambientIntensity");
    uniformDirection=gl()->glGetUniformLocation(program,"light.direction");
    uniformDiffuseIntensity=gl()->glGetUniformLocation(program,"light.diffuseIntensity");
    uniformModelColor=gl()->glGetUniformLocation(program,"modelColor");
}

void LightShader::clearUniforms(){
    uniformLightColor=0;
    uniformAmbientIntensity=0;
    uniformDirection=0;
    uniformDiffuseIntensity=0;
}
