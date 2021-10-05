#include "qssloader.h"

void qssLoader(QWidget*target,QString qssPath){
    QFile file(qssPath);
    if(!file.open(QIODevice::ReadOnly)){
        qDebug()<<"Unable to apply QSS from "<<qssPath<<" to "<<target;
        return;
    }
    QString qss=QString::fromStdString(file.readAll().toStdString());
    target->setStyleSheet(qss);
    file.close();
}
