#pragma once

#include <QListWidgetItem>

class ModelPropertiesWidget;
class Mesh;

class ListWidgetItem : public QListWidgetItem{
    ModelPropertiesWidget*widget;
public:
    ListWidgetItem(QString text="Model");
    virtual ~ListWidgetItem();

    ModelPropertiesWidget* getModelPropertiesWidget(){return widget;}
    void setModelPropertiesWidget(ModelPropertiesWidget*widget){this->widget=widget;}
    QString getText(){return text();}
};
