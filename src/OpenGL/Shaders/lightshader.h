#include "../shader.h"

class LightShader : public Shader{
    GLuint uniformModelColor=0,uniformIsTex=0;
protected:
    virtual void populateUniformLocations();
    virtual void clearUniformLocations();
public:
    LightShader(){}
};
