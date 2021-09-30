#include "src/OpenGL/shader.h"

class GridShader : public Shader{
    GLuint uniformModelColor=0;
protected:
    virtual void setupUniforms();
    virtual void clearUniforms();
public:
    GridShader(): Shader(){}

    GLuint getModelColorLocation(){return uniformModelColor;}
};
