#include "glwidget.h"

#include <QMainWindow>

class MainWindow : public QMainWindow{
    Q_OBJECT
    GLWidget*glwidget;
public:
    MainWindow(QWidget*parent=NULL);
};
