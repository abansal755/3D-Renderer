#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QElapsedTimer>

#include "src/OpenGL/camera.h"

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core{
    Q_OBJECT
    bool wPressed=false,aPressed=false,sPressed=false,dPressed=false;

    int lastX,lastY,xChange=0,yChange=0;
    GLfloat lastTime;
    QElapsedTimer timer;

    Camera*camera;
protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

    void keyPressEvent(QKeyEvent*event);
    void keyReleaseEvent(QKeyEvent*event);
    void mouseMoveEvent(QMouseEvent*event);
    void mousePressEvent(QMouseEvent*event);
public:
    GLWidget(QWidget*parent=NULL);
    ~GLWidget();

    bool isWPressed(){return wPressed;}
    bool isAPressed(){return aPressed;}
    bool isSPressed(){return sPressed;}
    bool isDPressed(){return dPressed;}

    int getXChange();
    int getYChange();
};
