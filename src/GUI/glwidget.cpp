#include "glwidget.h"
#include "src/OpenGL/version.h"
#include "src/OpenGL/camera.h"
#include "lib/glm/gtc/type_ptr.hpp"

#include <string>
#include <QDebug>
#include <QKeyEvent>

GLWidget::GLWidget(QWidget*parent):QOpenGLWidget(parent){
    connect(this,SIGNAL(frameSwapped()),this,SLOT(update()));
    setFocusPolicy(Qt::StrongFocus);
}

GLWidget::~GLWidget(){
    for (Mesh* mesh : meshes) delete mesh;
    for (Shader* shader : shaders) delete shader;
    delete camera;
    delete light;
}

void GLWidget::clearBuffer(){
    gl()->glClearColor(0,0,0,1);
    gl()->glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

void GLWidget::resizeGL(int width, int height){
    gl()->glViewport(0,0,width,height);
    camera->setAspect((GLfloat)width/height);
}

void GLWidget::initializeGL(){
    gl()->glEnable(GL_DEPTH_TEST);
    gl()->glProvokingVertex(GL_FIRST_VERTEX_CONVENTION);

    std::string vPath = "C:/Users/Akshit/Documents/C++/Qt/OpenGL-Qt-Trial/shaders/shader/shader.vert";
    std::string fPath = "C:/Users/Akshit/Documents/C++/Qt/OpenGL-Qt-Trial/shaders/shader/shader.frag";
    shaders.push_back(new Shader(vPath, fPath));

    camera=new Camera(glm::vec3(-4,0,0),glm::vec3(0,1,0),
                      0,0,10,0.005,
                      PI/4,1,0.01,100);

    light=new Light();

    std::vector<Vertex> vertices={
        //  x   y   z   nx, ny, nz
        {-1, -1, -1,   0, -1,  0},  // 0, nv front
        {-1, -1,  1,   0,  0,  1},  // 1, nv top
        { 1, -1, -1,   0,  0,  0},  // 2
        { 1, -1,  1,   1,  0,  0},  // 3, nv right
        { 1,  1, -1,   0,  1,  0},  // 4, nv back
        { 1,  1,  1,   0,  0,  0},  // 5
        {-1,  1, -1,   0,  0, -1},  // 6, nv bottom
        {-1,  1,  1,  -1,  0,  0}  // 7, nv left
    };
    std::vector<unsigned int> indices={
        0, 2, 3,   0, 3, 1, // front
        4, 6, 7,   4, 7, 5, // back
        3, 2, 4,   3, 4, 5, // right
        7, 6, 0,   7, 0, 1, // left
        6, 4, 2,   6, 2, 0, // bottom
        1, 3, 5,   1, 5, 7  // top
    };
    meshes.push_back(new Mesh(vertices,indices));

    timer.start();
    lastTime=(GLfloat)timer.elapsed()/1000;
}

void GLWidget::paintGL(){
    clearBuffer();

    GLfloat currTime=(GLfloat)timer.elapsed()/1000;
    GLfloat deltaTime=currTime-lastTime;
    lastTime=currTime;

    camera->mouseControl(getXChange(),getYChange());
    camera->keyControl(this,deltaTime);

    shaders[0]->useShader();
    GLuint uniformModel=shaders[0]->getModelLocation();
    GLuint uniformProjection=shaders[0]->getProjectionLocation();
    GLuint uniformView=shaders[0]->getViewLocation();
    GLuint uniformColor=shaders[0]->getColorLocation();
    GLuint uniformAmbientIntensity=shaders[0]->getAmbientIntensityLocation();
    GLuint uniformDirection=shaders[0]->getDirectionLocation();
    GLuint uniformDiffuseIntensity=shaders[0]->getDiffuseIntensityLocation();
    light->setDirection(camera->getFront());
    light->useLight(uniformColor,uniformAmbientIntensity,uniformDirection,uniformDiffuseIntensity);
    glm::mat4 model(1);
    gl()->glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    gl()->glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(camera->calculateProjectionMatrix()));
    gl()->glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera->calculateViewMatrix()));
    meshes[0]->renderMesh();

    Shader::unUseShader();
}

void GLWidget::keyPressEvent(QKeyEvent *event){
    if(event->key()==Qt::Key_W) wPressed=true;
    else if(event->key()==Qt::Key_A) aPressed=true;
    else if(event->key()==Qt::Key_S) sPressed=true;
    else if(event->key()==Qt::Key_D) dPressed=true;
    else QWidget::keyPressEvent(event);
}

void GLWidget::keyReleaseEvent(QKeyEvent *event){
    if(event->key()==Qt::Key_W) wPressed=false;
    else if(event->key()==Qt::Key_A) aPressed=false;
    else if(event->key()==Qt::Key_S) sPressed=false;
    else if(event->key()==Qt::Key_D) dPressed=false;
    else QWidget::keyReleaseEvent(event);
}

void GLWidget::mouseMoveEvent(QMouseEvent *event){
    xChange+=event->x()-lastX;
    yChange+=lastY-event->y();

    lastX=event->x();
    lastY=event->y();
}

void GLWidget::mousePressEvent(QMouseEvent *event){
    lastX=event->x();
    lastY=event->y();
}

int GLWidget::getXChange(){
    int ans=xChange;
    xChange=0;
    return ans;
}

int GLWidget::getYChange(){
    int ans=yChange;
    yChange=0;
    return ans;
}
