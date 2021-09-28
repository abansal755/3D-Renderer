#include "listwidgetitem.h"
#include "modelpropertieswidget.h"

#include "src/OpenGL/mesh.h"

ListWidgetItem::ListWidgetItem(){
    widget=new ModelPropertiesWidget;
}

ListWidgetItem::~ListWidgetItem(){
    delete widget;
}
