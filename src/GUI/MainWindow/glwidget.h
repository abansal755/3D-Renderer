#include "src/OpenGL/mesh.h"
#include "src/OpenGL/texture.h"
#include "src/OpenGL/light.h"

#include <QOpenGLWidget>
#include <vector>
#include <QElapsedTimer>
#include <QColor>
#include <QOpenGLFunctions_3_3_Core>

class ListWidget;
class Camera;
class SettingsWidget;
class LightShader;
class GridModel;
class GridShader;

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core{
    Q_OBJECT
    bool wPressed=false,aPressed=false,sPressed=false,dPressed=false;

    int lastX,lastY,xChange=0,yChange=0;

    LightShader*flatShader;
    GridShader*gridShader;
    Mesh*planeMesh,*cubeMesh;
    Camera*camera;
    Light*light;
    GridModel*grid;

    GLfloat lastTime;
    QElapsedTimer timer;

    ListWidget*modelsListWidget;
    SettingsWidget*settingsWidget;
public:
    GLWidget(ListWidget*modelsListWidget,SettingsWidget*settingsWidget,QWidget*parent=NULL);
    ~GLWidget();

    bool isWPressed(){return wPressed;}
    bool isAPressed(){return aPressed;}
    bool isSPressed(){return sPressed;}
    bool isDPressed(){return dPressed;}

    int getXChange();
    int getYChange();

    Mesh* getCubeMesh(){return cubeMesh;}
    Mesh* getPlaneMesh(){return planeMesh;}
    LightShader* getFlatShader(){return flatShader;}
    GridModel* getGridModel(){return grid;}
    QImage renderViewport();
protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

    void keyPressEvent(QKeyEvent*event);
    void keyReleaseEvent(QKeyEvent*event);
    void mouseMoveEvent(QMouseEvent*event);
    void mousePressEvent(QMouseEvent*event);
};
