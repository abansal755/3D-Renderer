#include "modelpropertieswidget.h"

#include <QListWidgetItem>

class ListWidgetItem : public QListWidgetItem{
    ModelPropertiesWidget*widget;
public:
    ListWidgetItem();
    ~ListWidgetItem();

    ModelPropertiesWidget* getModelPropertiesWidget(){return widget;}
};
