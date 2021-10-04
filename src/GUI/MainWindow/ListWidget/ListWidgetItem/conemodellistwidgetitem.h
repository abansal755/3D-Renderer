#include "src/GUI/MainWindow/ListWidget/listwidgetitem.h"

class GLWidget;

class ConeModelListWidgetItem : public ListWidgetItem{
public:
    ConeModelListWidgetItem(GLWidget*glwidget,QString text="Model");
};
