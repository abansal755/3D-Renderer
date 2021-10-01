#include "flatmodellistwidgetitem.h"
#include "src/GUI/MainWindow/ListWidget/ModelPropertiesWidget/flatmodelpropertieswidget.h"

FlatModelListWidgetItem::FlatModelListWidgetItem(QString text)
    :ListWidgetItem(text)
{
    setModelPropertiesWidget(new FlatModelPropertiesWidget(this,text));
}
