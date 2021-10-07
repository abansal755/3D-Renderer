#include "src/GUI/MainWindow/ListWidget/listwidgetitem.h"

class GLWidget;

class SphereModelListWidgetItem : public ListWidgetItem{
public:
    SphereModelListWidgetItem(GLWidget*glwidget,QString text="Model");
};
