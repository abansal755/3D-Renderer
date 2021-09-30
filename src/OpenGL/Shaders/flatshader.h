#include "src/OpenGL/shader.h"

class FlatShader : public Shader{
    GLuint uniformLightColor=0,uniformAmbientIntensity=0;
    GLuint uniformDirection=0,uniformDiffuseIntensity=0;
    GLuint uniformModelColor=0;
protected:
    virtual void setupUniforms();
    virtual void clearUniforms();
public:
    FlatShader():Shader(){}

    GLuint getLightColorLocation(){return uniformLightColor;}
    GLuint getAmbientIntensityLocation(){return uniformAmbientIntensity;}
    GLuint getDirectionLocation(){return uniformDirection;}
    GLuint getDiffuseIntensityLocation(){return uniformDiffuseIntensity;}
    GLuint getModelColorLocation(){return uniformModelColor;}
};
