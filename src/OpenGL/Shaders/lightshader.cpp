#include "lightshader.h"

LightShader::LightShader(){
    directionalLightUniforms.assign(MAX_DIRECTIONAL_LIGHTS,DirectionalLightUniform());
}

void LightShader::populateUniformLocations(){
    uniformModelColor=glGetUniformLocation(getShaderID(),"modelColor");
    uniformIsTex=glGetUniformLocation(getShaderID(),"isTex");
    uniformNumDirectionalLights=glGetUniformLocation(getShaderID(),"numDirectionalLights");

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
    uniformNumDirectionalLights=0;

    for(auto& uniform:directionalLightUniforms) uniform=DirectionalLightUniform();
}
