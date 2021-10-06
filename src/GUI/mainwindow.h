#include "MainWindow/glwidget.h"
#include "MainWindow/listwidget.h"
#include "aboutdialog.h"

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
    AboutDialog*aboutDialog;

    int planeCount=0,cubeCount=0,coneCount=0;
    void resetCounts();
protected:
    virtual void closeEvent(QCloseEvent*event);
private slots:
    void exitApp();
    void addPlane();
    void addCube();
    void addCone();
    void settings();
    void about();
    void newScene();
    void renderViewport();
public:
    MainWindow(QWidget*parent=NULL);
    ~MainWindow();
};
