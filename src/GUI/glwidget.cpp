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
    delete brickTex;
    delete dirtTex;
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

    std::vector<Vertex> vertices = {
        //x,y,z		u,v
        {-1,-1,-1,	0,0},
        {1,-1,-1,	1,0},
        {0,1,-1,	0.5,0},
        {0,0,1,		0.5,1}
    };
    std::vector<unsigned int> indices = {
        0,2,1,
        0,1,3,
        0,3,2,
        1,2,3
    };
    meshes.push_back(new Mesh(vertices, indices));

    std::vector<Vertex> vertices2 = {
        //x,y,z		u,v
        {-1,-1,0,	0,0},
        {1,-1,0,    2,0},
        {1,1,0,		2,2},
        {-1,1,0,	0,2}
    };
    std::vector<unsigned int> indices2 = {
        0,1,2,
        2,3,0
    };
    meshes.push_back(new Mesh(vertices2, indices2));

    std::string vPath = "C:/Users/Akshit/Documents/C++/Qt/OpenGL-Qt-Trial/shaders/shader/shader.vert";
    std::string fPath = "C:/Users/Akshit/Documents/C++/Qt/OpenGL-Qt-Trial/shaders/shader/shader.frag";
    shaders.push_back(new Shader(vPath, fPath));

    camera=new Camera(glm::vec3(-4,1,0),glm::vec3(0,1,0),
                      0,0,10,0.005,
                      PI/4,1,0.01,100);

    std::string brickPath="C:/Users/Akshit/Documents/C++/Qt/OpenGL-Qt-Trial/textures/brick.png";
    std::string dirtPath="C:/Users/Akshit/Documents/C++/Qt/OpenGL-Qt-Trial/textures/dirt.png";
    brickTex=new Texture(brickPath);
    dirtTex=new Texture(dirtPath);

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
    glm::mat4 model(1);
    model = glm::translate(model, glm::vec3(0, 1, 0));
    model = glm::rotate(model, PI / 2, glm::vec3(0, -1, 0));
    model = glm::rotate(model, PI / 2, glm::vec3(-1, 0, 0));
    gl()->glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    gl()->glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(camera->calculateProjectionMatrix()));
    gl()->glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera->calculateViewMatrix()));
    brickTex->useTexture();
    meshes[0]->renderMesh();

    model = glm::mat4(1);
    model = glm::rotate(model, -PI / 2, glm::vec3(1, 0, 0));
    model = glm::scale(model, glm::vec3(5, 5, 5));
    gl()->glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    dirtTex->useTexture();
    meshes[1]->renderMesh();

    Texture::unUseTexture();
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
