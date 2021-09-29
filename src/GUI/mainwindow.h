#include "glwidget.h"
#include "listwidget.h"

#include <QMainWindow>
#include <QMenuBar>
#include <QHBoxLayout>
#include <QVBoxLayout>

class MainWindow : public QMainWindow{
    Q_OBJECT
    QWidget*central;
    GLWidget*glwidget;
    ListWidget*listWidget;
    QHBoxLayout*hb1;
    QVBoxLayout*vb1;

    int cubeCount=0;
private slots:
    void exitApp();
    void addCube();
public:
    MainWindow(QWidget*parent=NULL);
};
