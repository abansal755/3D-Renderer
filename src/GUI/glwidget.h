#include "src/OpenGL/mesh.h"
#include "src/OpenGL/version.h"
#include "src/OpenGL/shader.h"
#include "src/OpenGL/texture.h"

#include <QOpenGLWidget>
#include <vector>
#include <QElapsedTimer>

class Camera;

class GLWidget : public QOpenGLWidget{
    Q_OBJECT
    bool wPressed=false,aPressed=false,sPressed=false,dPressed=false;

    int lastX,lastY,xChange=0,yChange=0;

    void clearBuffer();

    std::vector<Mesh*> meshes;
    std::vector<Shader*> shaders;
    Camera*camera;
    Texture*brickTex,*dirtTex;

    GLfloat lastTime;
    QElapsedTimer timer;
public:
    GLWidget(QWidget*parent=NULL);
    ~GLWidget();

    bool isWPressed(){return wPressed;}
    bool isAPressed(){return aPressed;}
    bool isSPressed(){return sPressed;}
    bool isDPressed(){return dPressed;}

    int getXChange();
    int getYChange();
protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

    void keyPressEvent(QKeyEvent*event);
    void keyReleaseEvent(QKeyEvent*event);
    void mouseMoveEvent(QMouseEvent*event);
    void mousePressEvent(QMouseEvent*event);
};
