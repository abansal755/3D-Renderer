#pragma once

#include "propertieswidget.h"

#include <QListWidgetItem>

class ListWidgetItem : public QListWidgetItem{
    PropertiesWidget*widget;
public:
    ListWidgetItem(QString text);
    virtual ~ListWidgetItem();

    void setPropertiesWidget(PropertiesWidget*widget){this->widget=widget;}
    PropertiesWidget* getPropertiesWidget(){return widget;}
};
