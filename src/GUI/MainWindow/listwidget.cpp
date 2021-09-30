#include "listwidget.h"
#include "ListWidget/listwidgetitem.h"
#include "ListWidget/modelpropertieswidget.h"
#include "src/OpenGL/Models/flatmodel.h"

#include <QDebug>

ListWidget::ListWidget(QVBoxLayout*layout,QWidget*parent):layout(layout),QListWidget(parent){
    connect(this,SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),this,SLOT(currentItemChanged(QListWidgetItem*,QListWidgetItem*)));
}

ListWidgetItem* ListWidget::getCustomCurrentItem(){
    return (ListWidgetItem*)currentItem();
}

ListWidgetItem* ListWidget::getCustomItem(int row){
    return (ListWidgetItem*)item(row);
}

void ListWidget::currentItemChanged(QListWidgetItem*currPtr,QListWidgetItem*prevPtr){
    ListWidgetItem*curr=(ListWidgetItem*)currPtr;
    ListWidgetItem*prev=(ListWidgetItem*)prevPtr;

    if(prev){
        layout->removeWidget(prev->getModelPropertiesWidget());
        prev->getModelPropertiesWidget()->hide();
    }
    if(curr){
        layout->addWidget(curr->getModelPropertiesWidget());
        curr->getModelPropertiesWidget()->show();
    }
}

std::vector<Model*> ListWidget::getModels(){
    std::vector<Model*> models;
    for(int i=0;i<count();i++){
        FlatModel* model=getCustomItem(i)->getModelPropertiesWidget()->getModel();
        models.push_back(model);
    }
    return models;
}
