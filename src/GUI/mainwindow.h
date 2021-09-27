#include "glwidget.h"

#include <QMainWindow>
#include <QMenuBar>

class MainWindow : public QMainWindow{
    Q_OBJECT
    GLWidget*glwidget;
private slots:
    void exitApp();
public:
    MainWindow(QWidget*parent=NULL);
};
