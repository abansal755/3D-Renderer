#include "MainWindow/glwidget.h"
#include "MainWindow/listwidget.h"

#include <QMainWindow>
#include <QMenuBar>
#include <QHBoxLayout>
#include <QVBoxLayout>

class SettingsDialog;

class MainWindow : public QMainWindow{
    Q_OBJECT
    QWidget*central;
    GLWidget*glwidget;
    ListWidget*listWidget;
    QHBoxLayout*hb1;
    QVBoxLayout*vb1;

    SettingsDialog*settingsDialog;

    int cubeCount=0;
private slots:
    void exitApp();
    void addCube();
    void settings();
public slots:
    void setBGColor(const QColor& color);
    void setLightColor(const QColor& color);
public:
    MainWindow(QWidget*parent=NULL);
};
