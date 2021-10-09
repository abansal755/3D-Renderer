#include "listwidget.h"

ListWidget::ListWidget(QVBoxLayout *layout, QWidget *parent)
    :layout(layout)
{
    connect(this,
            SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
            this,
            SLOT(currentItemChangedSlot(QListWidgetItem*,QListWidgetItem*)));
}

void ListWidget::currentItemChangedSlot(QListWidgetItem *currPtr,
                                    QListWidgetItem *prevPtr)
{
    ListWidgetItem*curr=(ListWidgetItem*)currPtr;
    ListWidgetItem*prev=(ListWidgetItem*)prevPtr;

    if(prev){
        layout->removeWidget(prev->getPropertiesWidget());
        prev->getPropertiesWidget()->hide();
    }
    if(curr){
        layout->addWidget(curr->getPropertiesWidget());
        curr->getPropertiesWidget()->show();
    }
}
