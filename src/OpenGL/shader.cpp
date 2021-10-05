#include "shader.h"

#include <QDebug>
#include <fstream>
#include <QFile>

Shader::Shader(){
    initializeOpenGLFunctions();
}

void Shader::loadShader(QString& vPath, QString& fPath) {
    clearShader();

    program = glCreateProgram();
    if (!program) {
        qDebug() << "Error creating shader program\n";
        return;
    }

    std::string vCode = readFile(vPath), fCode = readFile(fPath);
    addShader(vCode, GL_VERTEX_SHADER);
    addShader(fCode, GL_FRAGMENT_SHADER);

    GLint result;
    GLchar log[1024];

    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &result);
    if (!result) {
        glGetProgramInfoLog(program, sizeof(log), NULL, log);
        qDebug() << "Error linking shader program\n" << log;
        return;
    }

    glValidateProgram(program);
    glGetShaderiv(program, GL_VALIDATE_STATUS, &result);
    if (!result) {
        glGetProgramInfoLog(program, sizeof(log), NULL, log);
        qDebug() << "Error validating shader program\n" << log;
        return;
    }

    uniformModel = glGetUniformLocation(program, "model");
    uniformProjection = glGetUniformLocation(program, "projection");
    uniformView = glGetUniformLocation(program, "view");
    setupUniforms();
}

void Shader::clearShader() {
    if (!program) glDeleteProgram(program);
    uniformModel = 0;
    uniformProjection = 0;
    uniformView = 0;
    clearUniforms();
}

Shader::~Shader() {
    clearShader();
}

void Shader::addShader(std::string& shaderCode, GLenum shaderType) {
    GLuint shader = glCreateShader(shaderType);

    const GLchar* code[1];
    code[0] = &shaderCode[0];

    GLint codeLength[1];
    codeLength[0] = shaderCode.length();

    glShaderSource(shader, 1, code, codeLength);
    glCompileShader(shader);

    GLint result;
    GLchar log[1024];

    glGetProgramiv(shader, GL_COMPILE_STATUS, &result);
    if (!result) {
        glGetProgramInfoLog(shader, sizeof(log), NULL, log);
        qDebug() << "Error compiling shader\n" << log;
        return;
    }

    glAttachShader(program, shader);
}

void Shader::useShader() {
    glUseProgram(program);
}

void Shader::unUseShader() {
    glUseProgram(0);
}

std::string Shader::readFile(QString& path) {
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly)) return "";
    return file.readAll().toStdString();
    file.close();
}
