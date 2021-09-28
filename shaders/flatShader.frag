#version 330

flat in vec3 normal;

out vec4 color;

struct DirectionalLight{
    vec3 color;
    float ambientIntensity;

    vec3 direction;
    float diffuseIntensity;
};

uniform DirectionalLight directionalLight;
uniform vec4 modelColor;

void main(){
    vec4 ambientColor=vec4(directionalLight.color,1)*directionalLight.ambientIntensity;

    float diffuseFactor=max(dot(normalize(directionalLight.direction),normalize(normal)),0);
    vec4 diffuseColor=vec4(directionalLight.color,1)*directionalLight.diffuseIntensity*diffuseFactor;

    color=modelColor*(ambientColor+diffuseColor);
}
