#include "modelpropertieswidget.h"
#include "../ListWidgetItems/modellistwidgetitem.h"

#include <QVBoxLayout>

ModelPropertiesWidget::ModelPropertiesWidget(ModelListWidgetItem*item,
                                             QString text)
    :PropertiesWidget(item,text)
{
    model=new Model;
}

ModelPropertiesWidget::~ModelPropertiesWidget(){
    delete model;
}
