#include "GUI/mainwindow.h"
#include "version.h"

#include <QApplication>
#include <QDebug>

const Version version(0,1,0);

int main(int argc, char *argv[]){
    qDebug()<<"Version "<<version.toString();

    QApplication a(argc, argv);

    QSurfaceFormat format;
    format.setVersion(3,3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);

    MainWindow w;
    w.show();
    return a.exec();
}
