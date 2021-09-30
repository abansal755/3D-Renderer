#include "flatmodel.h"
#include "src/OpenGL/version.h"
#include "src/OpenGL/Shaders/flatshader.h"

void FlatModel::populateUniforms(){
    FlatShader*shader=(FlatShader*)getShader();
    GLuint uniformModelColor=shader->getModelColorLocation();
    gl()->glUniform4f(uniformModelColor,color.redF(),color.greenF(),color.blueF(),color.alphaF());
}
