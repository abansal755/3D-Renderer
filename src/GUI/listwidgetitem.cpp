#include "listwidgetitem.h"
#include "modelpropertieswidget.h"

#include "src/OpenGL/mesh.h"

ListWidgetItem::ListWidgetItem(QString text){
    widget=new ModelPropertiesWidget(this,text);
    setText(text);
}

ListWidgetItem::~ListWidgetItem(){
    delete widget;
}
