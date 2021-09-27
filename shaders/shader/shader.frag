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

void main(){
    vec4 ambientColor=vec4(directionalLight.color,1)*directionalLight.ambientIntensity;

    float diffuseFactor=max(dot(normalize(directionalLight.direction),normalize(normal)),0);
    vec4 diffuseColor=vec4(directionalLight.color,1)*directionalLight.diffuseIntensity*diffuseFactor;

    color=vec4(0.5,0.5,0.5,1)*(ambientColor+diffuseColor);
}
