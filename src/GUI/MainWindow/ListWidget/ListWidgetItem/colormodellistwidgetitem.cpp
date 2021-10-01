#include "colormodellistwidgetitem.h"
#include "src/GUI/MainWindow/ListWidget/ModelPropertiesWidget/colormodelpropertieswidget.h"

ColorModelListWidgetItem::ColorModelListWidgetItem(QString text)
    :ListWidgetItem(text)
{
    setModelPropertiesWidget(new ColorModelPropertiesWidget(this,text));
}
