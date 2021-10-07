#include "glwidget.h"
#include "src/OpenGL/camera.h"
#include "lib/glm/gtc/type_ptr.hpp"
#include "lib/glm/gtx/rotate_vector.hpp"
#include "listwidget.h"
#include "ListWidget/ListWidgetItem/colormodellistwidgetitem.h"
#include "ListWidget/ModelPropertiesWidget/colormodelpropertieswidget.h"
#include "src/GUI/settingswidget.h"
#include "src/OpenGL/Shaders/lightshader.h"
#include "src/OpenGL/Models/gridmodel.h"
#include "src/OpenGL/Shaders/gridshader.h"
#include "src/OpenGL/Models/colormodel.h"

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
    glViewport(0,0,width,height);
    camera->setAspect((GLfloat)width/height);
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

    QString vPathFlat = ":/shaders/lightshader.vert";
    QString fPathFlat = ":/shaders/lightshader.frag";
    flatShader=new LightShader;
    flatShader->loadShader(vPathFlat,fPathFlat);

    QString vPathGrid = ":/shaders/gridshader.vert";
    QString fPathGrid = ":/shaders/gridshader.frag";
    gridShader=new GridShader;
    gridShader->loadShader(vPathGrid,fPathGrid);

    grid=new GridModel;
    grid->setShader(gridShader);

    timer.start();
    lastTime=(GLfloat)timer.elapsed()/1000;
}

void GLWidget::paintGL(){
    QColor bgColor=settingsWidget->getBGColor();
    glClearColor(bgColor.redF(),bgColor.greenF(),bgColor.blueF(),bgColor.alphaF());
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

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

QImage GLWidget::renderViewport(){
//    unsigned char* data=new unsigned char[3*width*height];
//    gl()->glReadPixels(0,0,width,height,GL_RGB,GL_UNSIGNED_BYTE,data);
//    QImage image(width,height,QImage::Format_RGB888);
//    unsigned char* ptr=data;
//    for(int y=height-1;y>=0;y--){
//        for(int x=0;x<width;x++){
//            int r=*(ptr++);
//            int g=*(ptr++);
//            int b=*(ptr++);
//            image.setPixelColor(x,y,QColor(r,g,b));
//        }
//    }
//    delete[]data;
//    return image;
    return grabFramebuffer();
}

Mesh* GLWidget::getConeMesh(GLfloat radius,GLfloat height,GLint numLines){
    makeCurrent();

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    GLfloat theta=2*PI/numLines;
    for(int i=0;i<numLines;i++){
        glm::vec3 pos;
        pos.x=radius*glm::cos(i*theta);
        pos.y=0;
        pos.z=radius*glm::sin(i*theta);

        GLfloat d=radius*glm::cos(theta/2);
        GLfloat beta=glm::asin(d/glm::sqrt(height*height+d*d));
        glm::vec3 norm;
        norm.x=radius*glm::cos(beta)*glm::cos(i*theta+theta/2);
        norm.y=radius*glm::sin(beta);
        norm.z=radius*glm::cos(beta)*glm::sin(i*theta+theta/2);

        vertices.push_back(Vertex(pos,norm));
    }
    vertices.push_back(Vertex(0,0,0,0,-1,0));
    vertices.push_back(Vertex(0,height,0,0,0,0));
    for(int i=0;i<numLines;i++){
        indices.push_back(numLines);
        indices.push_back(i);
        indices.push_back((i+1)%numLines);
    }
    for(int i=0;i<numLines;i++){
        indices.push_back(i);
        indices.push_back((i+1)%numLines);
        indices.push_back(numLines+1);
    }

    return new Mesh(vertices,indices);
}

Mesh* GLWidget::getCylinderMesh(GLfloat radius, GLfloat height, GLint numLines){
    makeCurrent();

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    GLfloat theta=2*PI/numLines;
    for(int i=0;i<numLines;i++){
        //0 -> numLines-1
        glm::vec3 pos;
        pos.x=radius*glm::cos(i*theta);
        pos.y=0;
        pos.z=radius*glm::sin(i*theta);

        GLfloat d=radius*glm::cos(theta/2);
        GLfloat beta=glm::asin(d/glm::sqrt(height*height+d*d));
        glm::vec3 norm;
        norm.x=radius*glm::cos(beta)*glm::cos(i*theta+theta/2);
        norm.y=radius*glm::sin(beta);
        norm.z=radius*glm::cos(beta)*glm::sin(i*theta+theta/2);

        vertices.push_back(Vertex(pos,norm));
    }
    for(int i=0;i<numLines;i++){
        //numLines -> 2*numLines-1
        glm::vec3 pos;
        pos.x=radius*glm::cos(i*theta);
        pos.y=height;
        pos.z=radius*glm::sin(i*theta);

        GLfloat d=radius*glm::cos(theta/2);
        GLfloat beta=glm::asin(d/glm::sqrt(height*height+d*d));
        glm::vec3 norm;
        norm.x=radius*glm::cos(beta)*glm::cos(i*theta+theta/2);
        norm.y=radius*glm::sin(beta);
        norm.z=radius*glm::cos(beta)*glm::sin(i*theta+theta/2);

        vertices.push_back(Vertex(pos,norm));
    }
    vertices.push_back(Vertex(0,0,0,0,-1,0));//2*numLines
    vertices.push_back(Vertex(0,height,0,0,1,0));//2*numLines+1

    for(int i=0;i<numLines;i++){
        indices.push_back(2*numLines);
        indices.push_back(i);
        indices.push_back((i+1)%numLines);
    }
    for(int i=0;i<numLines;i++){
        indices.push_back(2*numLines+1);
        indices.push_back(i+numLines);
        indices.push_back((i+1)%numLines+numLines);
    }
    for(int i=0;i<numLines;i++){
        indices.push_back(i);
        indices.push_back((i+1)%numLines);
        indices.push_back(i+numLines);
    }
    for(int i=0;i<numLines;i++){
        indices.push_back(i+numLines);
        indices.push_back((i+1)%numLines+numLines);
        indices.push_back((i+1)%numLines);
    }

    return new Mesh(vertices,indices);
}

Mesh* GLWidget::getSphereMesh(GLfloat radius,GLint numLines){
    makeCurrent();

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    GLfloat theta=PI/(numLines+1);
    GLfloat alpha=2*PI/(numLines+1);
    for(int i=0;i<=numLines+1;i++){
        for(int j=0;j<=numLines+1;j++){
            glm::vec3 pos;
            pos.x=radius*glm::cos(-PI/2+i*theta)*glm::cos(j*alpha);
            pos.y=radius*glm::sin(-PI/2+i*theta);
            pos.z=radius*glm::cos(-PI/2+i*theta)*glm::sin(j*alpha);

            glm::vec3 norm;
            norm.x=radius*glm::cos(-PI/2+i*theta+theta/2)*glm::cos(j*alpha+alpha/2);
            norm.y=radius*glm::sin(-PI/2+i*theta+theta/2);
            norm.z=radius*glm::cos(-PI/2+i*theta+theta/2)*glm::sin(j*alpha+alpha/2);

            vertices.push_back(Vertex(pos,norm));
        }
    }


    unsigned int n=numLines+2;
    for(int i=0;i<=numLines;i++){
        for(int j=0;j<=numLines;j++){
            std::vector<unsigned int> quad={
                n*i+j,n*i+j+1,n*(i+1)+j+1,
                n*i+j,n*(i+1)+j,n*(i+1)+j+1
            };
            for(unsigned int i:quad) indices.push_back(i);
        }
    }

    return new Mesh(vertices,indices);
}
