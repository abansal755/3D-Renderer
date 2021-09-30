#include "flatshader.h"
#include <QDebug>

void FlatShader::setupUniforms(){
    uniformLightColor=gl()->glGetUniformLocation(program,"light.color");
    uniformAmbientIntensity=gl()->glGetUniformLocation(program,"light.ambientIntensity");
    uniformDirection=gl()->glGetUniformLocation(program,"light.direction");
    uniformDiffuseIntensity=gl()->glGetUniformLocation(program,"light.diffuseIntensity");
    uniformModelColor=gl()->glGetUniformLocation(program,"modelColor");
}

void FlatShader::clearUniforms(){
    uniformLightColor=0;
    uniformAmbientIntensity=0;
    uniformDirection=0;
    uniformDiffuseIntensity=0;
}
