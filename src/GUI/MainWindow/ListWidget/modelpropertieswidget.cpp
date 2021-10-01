#include "modelpropertieswidget.h"
#include "listwidgetitem.h"

#include <QVBoxLayout>

ModelPropertiesWidget::ModelPropertiesWidget(ListWidgetItem*item,QString text)
    :item(item)
{
    QVBoxLayout*vb1=new QVBoxLayout;
        lineEdit1=new QLineEdit(text);
            connect(lineEdit1,SIGNAL(textChanged(const QString&)),this,SLOT(textChangedSlot(const QString&)));
        vb1->addWidget(lineEdit1);
        chb1=new QCheckBox("Visible");
            chb1->setCheckState(Qt::Checked);
        vb1->addWidget(chb1);
        container=new QWidget;
        vb1->addWidget(container);
    setLayout(vb1);
}

ModelPropertiesWidget::~ModelPropertiesWidget(){
    delete model;
}

void ModelPropertiesWidget::setText(QString text){
    lineEdit1->setText(text);
    textChangedSlot(text);
}

void ModelPropertiesWidget::textChangedSlot(const QString& text){
    item->setText(text);
}
