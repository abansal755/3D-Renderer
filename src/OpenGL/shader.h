#include "version.h"

#include <string>

class Shader{
    GLuint program = 0, uniformModel = 0, uniformProjection = 0, uniformView = 0;
    GLuint uniformLightColor=0,uniformAmbientIntensity=0;
    GLuint uniformDirection=0,uniformDiffuseIntensity=0;
    GLuint uniformModelColor=0;
    void addShader(std::string& shaderCode, GLenum shaderType);
    std::string readFile(std::string& path);

    Shader(const Shader& shader);
    Shader operator=(const Shader& shader);
public:
    Shader() {};
    Shader(std::string& vPath, std::string& fPath);
    ~Shader();

    void loadShader(std::string& vPath, std::string& fPath);
    void clearShader();

    GLuint getShaderID() { return program; }
    GLuint getModelLocation() { return uniformModel; }
    GLuint getProjectionLocation() { return uniformProjection; }
    GLuint getViewLocation() { return uniformView; }
    GLuint getLightColorLocation(){return uniformLightColor;}
    GLuint getAmbientIntensityLocation(){return uniformAmbientIntensity;}
    GLuint getDirectionLocation(){return uniformDirection;}
    GLuint getDiffuseIntensityLocation(){return uniformDiffuseIntensity;}
    GLuint getModelColorLocation(){return uniformModelColor;}

    bool empty() { return (program == 0); }

    void useShader();
    static void unUseShader();
};
