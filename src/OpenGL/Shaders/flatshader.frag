#version 330

flat in vec3 normal;

out vec4 color;

struct Light{
    vec3 color;
    float ambientIntensity;

    vec3 direction;
    float diffuseIntensity;
};

uniform Light light;
uniform vec4 modelColor;

void main(){
    vec4 ambientColor=vec4(light.color,1)*light.ambientIntensity;

    float diffuseFactor=max(dot(normalize(light.direction),normalize(normal)),0);
    vec4 diffuseColor=vec4(light.color,1)*light.diffuseIntensity*diffuseFactor;

    color=modelColor*(ambientColor+diffuseColor);
}
