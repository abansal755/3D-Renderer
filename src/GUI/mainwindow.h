#pragma once

#include "MainWindow/glwidget.h"
#include "MainWindow/listwidget.h"
#include "aboutdialog.h"

#include <QMainWindow>
#include <QMenuBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

class SettingsWidget;

class MainWindow : public QMainWindow{
    Q_OBJECT
    GLWidget*glwidget;
    ListWidget*listWidget;
    SettingsWidget*settingsWidget;
    AboutDialog*aboutDialog;

    int planeCount=0,cubeCount=0,coneCount=0,cylinderCount=0,sphereCount=0;
    void resetCounts();

    bool change=false;

    bool isColorJsonValid(QJsonObject json);
    QColor jsonToQColor(QJsonObject json);

    QNetworkAccessManager*manager;
protected:
    virtual void closeEvent(QCloseEvent*event);
private slots:
    void exitApp();
    void addPlane();
    void addCube();
    void addCone();
    void addCylinder();
    void addSphere();
    void settings();
    void about();
    int newScene();
    void renderViewport();
    void saveAs();

    void requestFinished(QNetworkReply*reply);
public slots:
    void loadScene(QString path="");
public:
    MainWindow(QWidget*parent=NULL);
    ~MainWindow();
};
