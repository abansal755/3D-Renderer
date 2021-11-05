#pragma once

#include "src/OpenGL/mesh.h"
#include "src/OpenGL/texture.h"
#include "src/OpenGL/light.h"

#include <QOpenGLWidget>
#include <vector>
#include <QElapsedTimer>
#include <QColor>
#include <QOpenGLFunctions_3_3_Core>

class MainWindow;
class ListWidget;
class Camera;
class SettingsWidget;
class LightShader;
class GridModel;
class GridShader;
class ColorModelListWidgetItem;

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core{
    Q_OBJECT
    bool wPressed=false,aPressed=false,sPressed=false,dPressed=false;

    int lastX,lastY,xChange=0,yChange=0;

    LightShader*flatShader,*phongShader;
    GridShader*gridShader;
    Mesh*planeMesh,*cubeMesh;
    Camera*camera;
    Light*light;
    GridModel*grid;

    GLfloat lastTime;
    QElapsedTimer timer;

    ListWidget*modelsListWidget;
    SettingsWidget*settingsWidget;
    MainWindow*mainWindow;

    QJsonObject objectToJson(ColorModelListWidgetItem*item);
    QJsonObject qColorToJson(QColor color,bool alpha=true);
public:
    GLWidget(ListWidget*modelsListWidget,SettingsWidget*settingsWidget,MainWindow*mainWindow,QWidget*parent=NULL);
    ~GLWidget();

    bool isWPressed(){return wPressed;}
    bool isAPressed(){return aPressed;}
    bool isSPressed(){return sPressed;}
    bool isDPressed(){return dPressed;}

    int getXChange();
    int getYChange();

    Mesh* getCubeMesh(){return cubeMesh;}
    Mesh* getPlaneMesh(){return planeMesh;}
    Mesh* getConeMesh(GLfloat radius=1,GLfloat height=1,GLint numLines=10);
    Mesh* getCylinderMesh(GLfloat radius=1,GLfloat height=1,GLint numLines=10);
    Mesh* getSphereMesh(GLfloat radius=1,GLint numLines=10);
    LightShader* getFlatShader(){return flatShader;}
    LightShader* getPhongShader(){return phongShader;}
    GridModel* getGridModel(){return grid;}
    QImage renderViewport();
    QJsonObject sceneToJson();
protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

    void keyPressEvent(QKeyEvent*event);
    void keyReleaseEvent(QKeyEvent*event);
    void mouseMoveEvent(QMouseEvent*event);
    void mousePressEvent(QMouseEvent*event);
};
