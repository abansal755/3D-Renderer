#include "../shader.h"

#include <vector>

const int MAX_DIRECTIONAL_LIGHTS=10;

struct DirectionalLightUniform{
    GLuint uniformLightColor=0,
    uniformAmbientIntensity=0,
    uniformDirection=0,
    uniformDiffuseIntensity=0;
};

class LightShader : public Shader{
    GLuint uniformModelColor=0,uniformIsTex=0;

    std::vector<DirectionalLightUniform> directionalLightUniforms;
protected:
    virtual void populateUniformLocations();
    virtual void clearUniformLocations();
public:
    LightShader();

    GLuint getModelColorLocation(){return uniformModelColor;}
    GLuint getIsTextureLocation(){return uniformIsTex;}
    std::vector<DirectionalLightUniform> getDirectionalLightUniforms(){return directionalLightUniforms;}
};
