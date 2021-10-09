#include "modellistwidgetitem.h"
#include "../PropertiesWidgets/modelpropertieswidget.h"

ModelListWidgetItem::ModelListWidgetItem(QString text)
    :ListWidgetItem(text)
{
    setPropertiesWidget(new ModelPropertiesWidget(this,text));
}
