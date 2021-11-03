#include "conemodellistwidgetitem.h"
#include "src/GUI/MainWindow/ListWidget/ModelPropertiesWidget/ColorModelPropertiesWidgets/conemodelpropertieswidget.h"

ConeModelListWidgetItem::ConeModelListWidgetItem(GLWidget*glwidget,
                                                 QString text)
    :ListWidgetItem(text)
{
    setModelPropertiesWidget(new ConeModelPropertiesWidget(this,glwidget,text));
    setObjectType(Cone);
}
