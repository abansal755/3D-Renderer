#version 330

in vec2 texCoord;
flat in vec3 normal;

out vec4 color;

struct DirectionalLight{
    vec3 lightColor;
    float ambientIntensity;
    vec3 direction;
    float diffuseIntensity;
};

uniform sampler2D texSampler;
const int MAX_DIRECTIONAL_LIGHTS=10;
uniform int isTex;
uniform vec3 modelColor;
uniform int numDirectionalLights;
uniform DirectionalLight directionalLights[MAX_DIRECTIONAL_LIGHTS];

void main(){
    int n=min(numDirectionalLights,MAX_DIRECTIONAL_LIGHTS);

    vec4 ambientColor=vec4(0,0,0,1);
    for(int i=0;i<n;i++){
        ambientColor+=vec4(directionalLights[i].lightColor,0)*directionalLights[i].ambientIntensity;
    }

    vec4 diffuseColor=vec4(0,0,0,1);
    for(int i=0;i<n;i++){
        float diffuseFactor=max(dot(normalize(normal),normalize(directionalLights[i].direction)),0);
        diffuseColor+=vec4(directionalLights[i].lightColor,0)*directionalLights[i].diffuseIntensity*diffuseFactor;
    }

    if(isTex==1) color=texture(texSampler,texCoord);
    else color=vec4(modelColor,1);
    color*=(ambientColor+diffuseColor);
}
