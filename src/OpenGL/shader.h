#pragma once

#include "version.h"

#include <string>
#include <QDebug>

class Shader{
    GLuint uniformModel = 0, uniformProjection = 0, uniformView = 0;
    void addShader(std::string& shaderCode, GLenum shaderType);
    std::string readFile(std::string& path);

    Shader(const Shader& shader);
    Shader operator=(const Shader& shader);
protected:
    GLuint program=0;
    virtual void setupUniforms(){}
    virtual void clearUniforms(){}
public:
    Shader(){}
    virtual ~Shader();

    void loadShader(std::string& vPath, std::string& fPath);
    void clearShader();

    GLuint getShaderID() { return program; }
    GLuint getModelLocation() { return uniformModel; }
    GLuint getProjectionLocation() { return uniformProjection; }
    GLuint getViewLocation() { return uniformView; }

    bool empty() { return (program == 0); }

    void useShader();
    static void unUseShader();
};
