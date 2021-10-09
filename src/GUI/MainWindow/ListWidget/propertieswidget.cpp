#include "listwidgetitem.h"

#include <QVBoxLayout>

PropertiesWidget::PropertiesWidget(ListWidgetItem*item,QString text)
    :item(item)
{
    QVBoxLayout*vb1=new QVBoxLayout;
        edit1=new QLineEdit(text);
            connect(edit1,SIGNAL(textChanged(const QString&)),this,SLOT(textChangedSlot(const QString&)));
        vb1->addWidget(edit1);
        container=new QWidget;
        vb1->addWidget(container);
    setLayout(vb1);
}

void PropertiesWidget::textChangedSlot(const QString& text){
    item->setText(text);
}
