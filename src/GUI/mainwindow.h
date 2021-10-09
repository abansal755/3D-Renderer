#include "MainWindow/glwidget.h"
#include "MainWindow/listwidget.h"

#include <QMainWindow>

class MainWindow : public QMainWindow{
    Q_OBJECT
    GLWidget*glwidget;
    ListWidget*models;

    int planeCount=0;
private slots:
    void exitSlot();
    void addPlane();
public:
    MainWindow(QWidget *parent=NULL);
};
