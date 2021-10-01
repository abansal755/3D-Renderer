#include "glwidget.h"
#include "src/OpenGL/camera.h"
#include "lib/glm/gtc/type_ptr.hpp"
#include "listwidget.h"
#include "ListWidget/ListWidgetItem/flatmodellistwidgetitem.h"
#include "ListWidget/ModelPropertiesWidget/flatmodelpropertieswidget.h"
#include "src/GUI/settingswidget.h"
#include "src/OpenGL/Shaders/flatshader.h"
#include "src/OpenGL/Models/gridmodel.h"
#include "src/OpenGL/Shaders/gridshader.h"
#include "src/OpenGL/Models/flatmodel.h"

#include <string>
#include <QDebug>
#include <QKeyEvent>

GLWidget::GLWidget(ListWidget*modelsListWidget,SettingsWidget*settingsWidget,QWidget*parent)
    :modelsListWidget(modelsListWidget),settingsWidget(settingsWidget),QOpenGLWidget(parent)
{
    connect(this,SIGNAL(frameSwapped()),this,SLOT(update()));
    setFocusPolicy(Qt::StrongFocus);
}

GLWidget::~GLWidget(){
    delete flatShader;
    delete planeMesh;
    delete cubeMesh;
    delete camera;
    delete light;
    delete grid;
    delete gridShader;
}

void GLWidget::resizeGL(int width, int height){
    gl()->glViewport(0,0,width,height);
    camera->setAspect((GLfloat)width/height);
}

void GLWidget::initializeGL(){
    gl()->glEnable(GL_DEPTH_TEST);
    gl()->glProvokingVertex(GL_FIRST_VERTEX_CONVENTION);

    camera=new Camera(glm::vec3(-4,0,0),glm::vec3(0,1,0),
                      0,0,10,0.005,
                      PI/4,1,0.01,100);

    light=new Light;

    std::vector<Vertex> verticesPlane={
        //x y z nx ny nz
        {-1,0,-1,0,1,0},  //bottom left
        {1,0,-1,0,1,0},   //bottom right
        {1,0,1,0,1,0}, //top right
        {-1,0,1,0,1,0}  //top left
    };
    std::vector<unsigned int> indicesPlane={
        0,1,2,
        2,3,0
    };
    planeMesh=new Mesh(verticesPlane,indicesPlane);

    std::vector<Vertex> verticesCube={
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
    std::vector<unsigned int> indicesCube={
        0, 2, 3,   0, 3, 1, // front
        4, 6, 7,   4, 7, 5, // back
        3, 2, 4,   3, 4, 5, // right
        7, 6, 0,   7, 0, 1, // left
        6, 4, 2,   6, 2, 0, // bottom
        1, 3, 5,   1, 5, 7  // top
    };
    cubeMesh=new Mesh(verticesCube,indicesCube);

    std::string vPathFlat = "C:/Users/Akshit/Documents/C++/Qt/3D Renderer/src/OpenGl/Shaders/flatshader.vert";
    std::string fPathFlat = "C:/Users/Akshit/Documents/C++/Qt/3D Renderer/src/OpenGl/Shaders/flatshader.frag";
    flatShader=new FlatShader;
    flatShader->loadShader(vPathFlat,fPathFlat);

    std::string vPathGrid = "C:/Users/Akshit/Documents/C++/Qt/3D Renderer/src/OpenGl/Shaders/gridshader.vert";
    std::string fPathGrid = "C:/Users/Akshit/Documents/C++/Qt/3D Renderer/src/OpenGl/Shaders/gridshader.frag";
    gridShader=new GridShader;
    gridShader->loadShader(vPathGrid,fPathGrid);

    grid=new GridModel;
    grid->setShader(gridShader);

    timer.start();
    lastTime=(GLfloat)timer.elapsed()/1000;
}

void GLWidget::paintGL(){
    QColor bgColor=settingsWidget->getBGColor();
    gl()->glClearColor(bgColor.redF(),bgColor.greenF(),bgColor.blueF(),bgColor.alphaF());
    gl()->glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    GLfloat currTime=(GLfloat)timer.elapsed()/1000;
    GLfloat deltaTime=currTime-lastTime;
    lastTime=currTime;

    camera->mouseControl(getXChange(),getYChange());
    camera->keyControl(this,deltaTime);
    camera->setMoveSpeed(settingsWidget->getCameraMoveSpeed());
    camera->setTurnSpeed(settingsWidget->getCameraTurnSpeed());
    camera->setFov(settingsWidget->getCameraFOV());
    camera->setZNear(settingsWidget->getCameraZNear());
    camera->setZFar(settingsWidget->getCameraZFar());

    light->setDirection(camera->getFront());
    light->setColor(settingsWidget->getLightColor());
    light->useLight(flatShader);
    light->setAmbientIntensity(settingsWidget->getAmbientLightIntensity());
    light->setDiffuseIntensity(settingsWidget->getDiffuseLightIntensity());

    grid->setColor(settingsWidget->getGridColor());
    if(settingsWidget->isChangeInGrid())
        grid->setGridConfig(settingsWidget->getGridNumLines(),settingsWidget->getGridSideLength());
    if(settingsWidget->isShowGridChecked()) grid->renderModel(camera);

    int countModels=modelsListWidget->count();
    for(int i=0;i<countModels;i++){
        ListWidgetItem*item=modelsListWidget->getCustomItem(i);
        ModelPropertiesWidget*widget=item->getModelPropertiesWidget();
        if(widget->isVisible()){
            Model*model=widget->getModel();
            model->renderModel(camera);
        }
    }
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
