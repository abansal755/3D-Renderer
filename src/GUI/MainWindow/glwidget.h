#include "src/OpenGL/mesh.h"
#include "src/OpenGL/version.h"
#include "src/OpenGL/shader.h"
#include "src/OpenGL/texture.h"
#include "src/OpenGL/light.h"
#include "src/OpenGL/model.h"

#include <QOpenGLWidget>
#include <vector>
#include <QElapsedTimer>
#include <QColor>

class ListWidget;
class Camera;
class SettingsWidget;

class GLWidget : public QOpenGLWidget{
    Q_OBJECT
    bool wPressed=false,aPressed=false,sPressed=false,dPressed=false;

    int lastX,lastY,xChange=0,yChange=0;

    Shader*flatShader;
    Mesh*cubeMesh;
    Camera*camera;
    Light*light;

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
    Shader* getFlatShader(){return flatShader;}
protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

    void keyPressEvent(QKeyEvent*event);
    void keyReleaseEvent(QKeyEvent*event);
    void mouseMoveEvent(QMouseEvent*event);
    void mousePressEvent(QMouseEvent*event);
};
