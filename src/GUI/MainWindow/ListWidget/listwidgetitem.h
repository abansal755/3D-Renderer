#pragma once

#include <QListWidgetItem>

class ModelPropertiesWidget;
class Mesh;

enum ObjectType{Default,Plane,Cube,Cone,Cylinder,Sphere};

class ListWidgetItem : public QListWidgetItem{
    ModelPropertiesWidget*widget;
    ObjectType objectType=Default;
public:
    ListWidgetItem(QString text="Model");
    virtual ~ListWidgetItem();

    ModelPropertiesWidget* getModelPropertiesWidget(){return widget;}
    void setModelPropertiesWidget(ModelPropertiesWidget*widget){this->widget=widget;}
    QString getText(){return text();}
    ObjectType getObjectType(){return objectType;}
    void setObjectType(ObjectType objectType){this->objectType=objectType;}
};
