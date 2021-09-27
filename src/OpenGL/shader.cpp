#include "shader.h"

#include <QDebug>
#include <fstream>

Shader::Shader(std::string& vPath, std::string& fPath) {
    loadShader(vPath, fPath);
}

void Shader::loadShader(std::string& vPath, std::string& fPath) {
    clearShader();

    program = gl()->glCreateProgram();
    if (!program) {
        qDebug() << "Error creating shader program\n";
        return;
    }

    std::string vCode = readFile(vPath), fCode = readFile(fPath);
    addShader(vCode, GL_VERTEX_SHADER);
    addShader(fCode, GL_FRAGMENT_SHADER);

    GLint result;
    GLchar log[1024];

    gl()->glLinkProgram(program);
    gl()->glGetProgramiv(program, GL_LINK_STATUS, &result);
    if (!result) {
        gl()->glGetProgramInfoLog(program, sizeof(log), NULL, log);
        qDebug() << "Error linking shader program\n" << log;
        return;
    }

    gl()->glValidateProgram(program);
    gl()->glGetShaderiv(program, GL_VALIDATE_STATUS, &result);
    if (!result) {
        gl()->glGetProgramInfoLog(program, sizeof(log), NULL, log);
        qDebug() << "Error validating shader program\n" << log;
        return;
    }

    uniformModel = gl()->glGetUniformLocation(program, "model");
    uniformProjection = gl()->glGetUniformLocation(program, "projection");
    uniformView = gl()->glGetUniformLocation(program, "view");
    uniformColor=gl()->glGetUniformLocation(program,"directionalLight.color");
    uniformAmbientIntensity=gl()->glGetUniformLocation(program,"directionalLight.ambientIntensity");
    uniformDirection=gl()->glGetUniformLocation(program,"directionalLight.direction");
    uniformDiffuseIntensity=gl()->glGetUniformLocation(program,"directionalLight.diffuseIntensity");
}

void Shader::clearShader() {
    if (!program) gl()->glDeleteProgram(program);
    uniformModel = 0;
    uniformProjection = 0;
    uniformView = 0;
    uniformColor=0;
    uniformAmbientIntensity=0;
    uniformDirection=0;
    uniformDiffuseIntensity=0;
}

Shader::~Shader() {
    clearShader();
}

void Shader::addShader(std::string& shaderCode, GLenum shaderType) {
    GLuint shader = gl()->glCreateShader(shaderType);

    const GLchar* code[1];
    code[0] = &shaderCode[0];

    GLint codeLength[1];
    codeLength[0] = shaderCode.length();

    gl()->glShaderSource(shader, 1, code, codeLength);
    gl()->glCompileShader(shader);

    GLint result;
    GLchar log[1024];

    gl()->glGetProgramiv(shader, GL_COMPILE_STATUS, &result);
    if (!result) {
        gl()->glGetProgramInfoLog(shader, sizeof(log), NULL, log);
        qDebug() << "Error compiling shader\n" << log;
        return;
    }

    gl()->glAttachShader(program, shader);
}

void Shader::useShader() {
    gl()->glUseProgram(program);
}

void Shader::unUseShader() {
    gl()->glUseProgram(0);
}

std::string Shader::readFile(std::string& path) {
    std::ifstream iFile(path);
    if (!iFile.is_open()) {
        qDebug() << "Unable to read from: " << QString::fromStdString(path) << '\n';
        return "";
    }
    std::string content, line;
    while (!iFile.eof()) {
        std::getline(iFile, line);
        content += line + '\n';
    }
    iFile.close();
    return content;
}
