#include "listwidgetitem.h"

ListWidgetItem::ListWidgetItem(){
    widget=new ModelPropertiesWidget;
}

ListWidgetItem::~ListWidgetItem(){
    delete widget;
}
