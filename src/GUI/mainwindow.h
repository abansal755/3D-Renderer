#include "MainWindow/glwidget.h"
#include "MainWindow/listwidget.h"

#include <QMainWindow>
#include <QMenuBar>
#include <QHBoxLayout>
#include <QVBoxLayout>

class SettingsWidget;

class MainWindow : public QMainWindow{
    Q_OBJECT
    QWidget*central;
    GLWidget*glwidget;
    ListWidget*listWidget;
    QHBoxLayout*hb1;
    QVBoxLayout*vb1;

    SettingsWidget*settingsWidget;

    int cubeCount=0;
private slots:
    void exitApp();
    void addCube();
    void settings();
public:
    MainWindow(QWidget*parent=NULL);
    ~MainWindow();
};
