#include "cylindermodellistwidgetitem.h"
#include "src/GUI/MainWindow/ListWidget/ModelPropertiesWidget/ColorModelPropertiesWidgets/cylindermodelpropertieswidget.h"

CylinderModelListWidgetItem::CylinderModelListWidgetItem(GLWidget*glwidget,
                                                 QString text)
    :ListWidgetItem(text)
{
    setModelPropertiesWidget(new CylinderModelPropertiesWidget(this,glwidget,text));
    setObjectType(Cylinder);
}
