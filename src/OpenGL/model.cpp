#include "model.h"
#include "lib/glm/gtc/type_ptr.hpp"

#include <QDebug>

Model::Model(Mesh *mesh, Material *mat, glm::mat4 modelMatrix)
    :mesh(mesh),mat(mat),modelMatrix(modelMatrix)
{
    initializeOpenGLFunctions();
}

void Model::renderModel(Camera*camera,std::vector<DirectionalLight*>&directionalLights){
    //bind shader
    LightShader* shader=mat->getShader();
    shader->useShader();

    //set uniform values
    GLuint modelLocation=shader->getModelLocation();
    glUniformMatrix4fv(modelLocation,1,GL_FALSE,glm::value_ptr(modelMatrix));

    //set camera values
    GLuint viewLocation=shader->getViewLocation();
    glUniformMatrix4fv(viewLocation,1,GL_FALSE,glm::value_ptr(camera->calculateViewMatrix()));
    GLuint projectionLocation=shader->getProjectionLocation();
    glUniformMatrix4fv(projectionLocation,1,GL_FALSE,glm::value_ptr(camera->calculateProjectionMatrix()));

    //set light values
    auto uniforms=shader->getDirectionalLightUniforms();

    GLuint numDirectionalLightsLocation=shader->getNumDirectionalLightsLocation();
    glUniform1i(numDirectionalLightsLocation,directionalLights.size());

    for(int i=0;i<std::min((int)directionalLights.size(),MAX_DIRECTIONAL_LIGHTS);i++){
        DirectionalLight* light=directionalLights[i];
        DirectionalLightUniform uniform=uniforms[i];

        QColor color=light->getColor();
        glUniform3f(uniform.uniformLightColor,color.redF(),color.greenF(),color.blueF());
        glUniform1f(uniform.uniformAmbientIntensity,light->getAmbientIntensity());
        glm::vec3 direction=light->getDirection();
        glUniform3f(uniform.uniformDirection,direction.x,direction.y,direction.z);
        glUniform1f(uniform.uniformDiffuseIntensity,light->getDiffuseIntensity());
    }

    //set texture and color
    QColor color=getMaterial()->getColor();
    glUniform3f(shader->getModelColorLocation(),color.redF(),color.greenF(),color.blueF());
    glUniform1i(shader->getIsTextureLocation(),mat->isTextureUsed());
    if(mat->isTextureUsed()) mat->getTexture()->useTexture();

    //render mesh
    mesh->renderMesh();

    //unuse texture
    if(mat->isTextureUsed()) mat->getTexture()->unUseTexture();

    //unbind shader
    shader->unUseShader();
}
