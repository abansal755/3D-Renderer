#include "glwidget.h"

#include <QMouseEvent>

GLWidget::GLWidget(QWidget *parent):QOpenGLWidget(parent){
    connect(this,SIGNAL(frameSwapped()),this,SLOT(update()));
    setFocusPolicy(Qt::StrongFocus);
}

GLWidget::~GLWidget(){
    delete camera;
    delete flatShader;
}

void GLWidget::initializeGL(){
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
    glProvokingVertex(GL_FIRST_VERTEX_CONVENTION);

    GLfloat theta=PI/4;
    GLfloat alpha=PI/6;
    GLfloat radius=8;

    camera=new Camera(glm::vec3(radius*glm::cos(theta)*glm::cos(alpha),
                                radius*glm::sin(alpha),radius*glm::cos(alpha)*glm::sin(theta)),
                                glm::vec3(0,1,0),
                                PI+theta,-alpha,10,0.005,
                                PI/4,1,0.01,100);

    flatShader=new LightShader;
    QString vPath=":/shaders/flatshader.vert";
    QString fPath=":/shaders/flatshader.frag";
    flatShader->loadShader(vPath,fPath);

    timer.start();
    lastTime=(GLfloat)timer.elapsed()/1000;
}

void GLWidget::resizeGL(int width, int height){
    glViewport(0,0,width,height);
    camera->setAspect((GLfloat)width/height);
}

void GLWidget::paintGL(){
    GLfloat currTime=(GLfloat)timer.elapsed()/1000;
    GLfloat deltaTime=currTime-lastTime;
    lastTime=currTime;

    camera->mouseControl(getXChange(),getYChange());
    camera->keyControl(this,deltaTime);
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

Mesh* GLWidget::getPlaneMesh(){
    makeCurrent();

    std::vector<Vertex> vertices={
        {-1,0,-1,   0,1,0,  0,0},
        {1,0,-1,    0,1,0,  1,0},
        {1,0,1,     0,1,0,  1,1},
        {-1,0,1,    0,1,0,  0,1}
    };
    std::vector<unsigned int> indices={
        0,1,2,
        2,3,0
    };

    return new Mesh(vertices,indices);
}
