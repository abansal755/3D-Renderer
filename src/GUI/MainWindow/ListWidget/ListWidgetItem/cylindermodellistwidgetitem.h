#include "src/GUI/MainWindow/ListWidget/listwidgetitem.h"

class GLWidget;

class CylinderModelListWidgetItem : public ListWidgetItem{
public:
    CylinderModelListWidgetItem(GLWidget*glwidget,QString text="Model");
};
