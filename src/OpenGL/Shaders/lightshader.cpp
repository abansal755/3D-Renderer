#include "lightshader.h"

LightShader::LightShader(){
    directionalLightUniforms.assign(MAX_DIRECTIONAL_LIGHTS,DirectionalLightUniform());

    GLuint uniformMaxNumLights=glGetUniformLocation(getShaderID(),"MAX_DIRECTIONAL_LIGHTS");
    glUniform1i(uniformMaxNumLights,MAX_DIRECTIONAL_LIGHTS);
}

void LightShader::populateUniformLocations(){
    uniformModelColor=glGetUniformLocation(getShaderID(),"modelColor");
    uniformIsTex=glGetUniformLocation(getShaderID(),"isTex");

    for(int i=0;i<MAX_DIRECTIONAL_LIGHTS;i++){
        std::string name="directionalLights["+std::to_string(i)+"].lightColor";
        directionalLightUniforms[i].uniformLightColor=glGetUniformLocation(getShaderID(),&name[0]);
        name="directionalLights["+std::to_string(i)+"].ambientIntensity";
        directionalLightUniforms[i].uniformAmbientIntensity=glGetUniformLocation(getShaderID(),&name[0]);
        name="directionalLights["+std::to_string(i)+"].direction";
        directionalLightUniforms[i].uniformDirection=glGetUniformLocation(getShaderID(),&name[0]);
        name="directionalLights["+std::to_string(i)+"].diffuseIntensity";
        directionalLightUniforms[i].uniformDiffuseIntensity=glGetUniformLocation(getShaderID(),&name[0]);
    }
}

void LightShader::clearUniformLocations(){
    uniformModelColor=0;
    uniformIsTex=0;
}
