#include "lightshader.h"

void LightShader::populateUniformLocations(){
    uniformModelColor=glGetUniformLocation(getShaderID(),"modelColor");
    uniformIsTex=glGetUniformLocation(getShaderID(),"isTex");
}

void LightShader::clearUniformLocations(){
    uniformModelColor=0;
    uniformIsTex=0;
}
