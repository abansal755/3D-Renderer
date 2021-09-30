#include "gridshader.h"

void GridShader::setupUniforms(){
    uniformModelColor=gl()->glGetUniformLocation(program,"modelColor");
}

void GridShader::clearUniforms(){
    uniformModelColor=0;
}
