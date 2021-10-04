#include "gridshader.h"

void GridShader::setupUniforms(){
    uniformModelColor=gl()->glGetUniformLocation(getShaderID(),"modelColor");
}

void GridShader::clearUniforms(){
    uniformModelColor=0;
}
