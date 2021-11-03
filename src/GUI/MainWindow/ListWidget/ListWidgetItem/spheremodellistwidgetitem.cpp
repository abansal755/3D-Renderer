#include "spheremodellistwidgetitem.h"
#include "src/GUI/MainWindow/ListWidget/ModelPropertiesWidget/ColorModelPropertiesWidgets/spheremodelpropertieswidget.h"

SphereModelListWidgetItem::SphereModelListWidgetItem(GLWidget*glwidget,
                                                 QString text)
    :ListWidgetItem(text)
{
    setModelPropertiesWidget(new SphereModelPropertiesWidget(this,glwidget,text));
    setObjectType(Sphere);
}
