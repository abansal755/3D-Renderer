#include "gridshader.h"

void GridShader::setupUniforms(){
    uniformModelColor=glGetUniformLocation(getShaderID(),"modelColor");
}

void GridShader::clearUniforms(){
    uniformModelColor=0;
}
