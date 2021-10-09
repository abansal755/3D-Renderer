#pragma once

#include "../listwidgetitem.h"

class ModelListWidgetItem : public ListWidgetItem{
public:
    ModelListWidgetItem(QString text="Model");
    ~ModelListWidgetItem(){}
};
