#include "model.h"
#include "lib/glm/gtc/type_ptr.hpp"

Model::Model(Mesh *mesh, Material *mat, glm::mat4 modelMatrix)
    :mesh(mesh),mat(mat),modelMatrix(modelMatrix)
{
    initializeOpenGLFunctions();
}

void Model::renderModel(){
    //bind shader
    LightShader* shader=mat->getShader();
    shader->useShader();

    //set uniform values
    GLuint modelLocation=shader->getModelLocation();
    glUniformMatrix4fv(modelLocation,1,GL_FALSE,glm::value_ptr(modelMatrix));

    //set camera values
    GLuint viewLocation=shader->getViewLocation();
    glUniformMatrix4fv(viewLocation,1,GL_FALSE,glm::value_ptr(getCamera()->calculateViewMatrix()));
    GLuint projectionLocation=shader->getProjectionLocation();
    glUniformMatrix4fv(projectionLocation,1,GL_FALSE,glm::value_ptr(getCamera()->calculateProjectionMatrix()));

    //set light values
    auto& vec=Model::directionalLights;
    auto uniforms=shader->getDirectionalLightUniforms();
    for(int i=0;i<std::min((int)vec.size(),MAX_DIRECTIONAL_LIGHTS);i++){
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
    glUniform1i(shader->getIsTextureLocation(),getMaterial()->isTextureUsed());
    if(getMaterial()->isTextureUsed()) getMaterial()->getTexture()->useTexture();

    //render mesh
    mesh->renderMesh();

    //unbind shader
    shader->unUseShader();
}

void Model::removeDirectionalLight(DirectionalLight*light){
    auto& vec=Model::directionalLights;
    for(int i=0;i<vec.size();i++){
        if(vec[i]==light){
            vec.erase(vec.begin()+i);
            break;
        }
    }
}
