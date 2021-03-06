#include "colormodel.h"
#include "src/OpenGL/Shaders/lightshader.h"

void ColorModel::populateUniforms(){
    LightShader*shader=(LightShader*)getShader();
    GLuint uniformModelColor=shader->getModelColorLocation();
    glUniform4f(uniformModelColor,color.redF(),color.greenF(),color.blueF(),color.alphaF());
}
