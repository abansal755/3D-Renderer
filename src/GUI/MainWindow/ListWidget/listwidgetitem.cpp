#include "listwidgetitem.h"
#include "modelpropertieswidget.h"

#include "src/OpenGL/mesh.h"

ListWidgetItem::ListWidgetItem(QString text){
    setText(text);
}

ListWidgetItem::~ListWidgetItem(){
    delete widget;
}
