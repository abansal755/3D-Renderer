#include "MainWindow/glwidget.h"
#include "MainWindow/listwidget.h"

#include <QMainWindow>
#include <QMenuBar>
#include <QHBoxLayout>
#include <QVBoxLayout>

class SettingsWidget;

class MainWindow : public QMainWindow{
    Q_OBJECT
    GLWidget*glwidget;
    ListWidget*listWidget;
    SettingsWidget*settingsWidget;

    int planeCount=0,cubeCount=0;
    void resetCounts();
private slots:
    void exitApp();
    void addPlane();
    void addCube();
    void settings();
    void newScene();
public:
    MainWindow(QWidget*parent=NULL);
    ~MainWindow();
};
