#include "modelpropertieswidget.h"
#include "src/OpenGL/model.h"
#include "lib/glm/gtc/matrix_transform.hpp"
#include "sliderfloat.h"
#include "listwidgetitem.h"

#include <QDebug>

ModelPropertiesWidget::ModelPropertiesWidget(ListWidgetItem*item,QString text)
    :item(item)
{
    model=new Model();

    colorDialog=new QColorDialog(model->getColor(),this);
    colorDialog->setOptions(QColorDialog::ShowAlphaChannel);
    btn1=new QPushButton("Change Color");

    translateX=new SliderFloat("translateX",NULL,-500,500,100);
    translateY=new SliderFloat("translateY",NULL,-500,500,100);
    translateZ=new SliderFloat("translateZ",NULL,-500,500,100);
    translateX->setValue(0);
    translateY->setValue(0);
    translateZ->setValue(0);

    rotateX=new SliderFloat("rotateX",NULL,-500,500,100);
    rotateY=new SliderFloat("rotateY",NULL,-500,500,100);
    rotateZ=new SliderFloat("rotateZ",NULL,-500,500,100);
    rotateX->setValue(0);
    rotateY->setValue(0);
    rotateZ->setValue(0);

    scaleX=new SliderFloat("scaleX",NULL,-500,500,100);
    scaleY=new SliderFloat("scaleY",NULL,-500,500,100);
    scaleZ=new SliderFloat("scaleZ",NULL,-500,500,100);
    scaleX->setValue(1);
    scaleY->setValue(1);
    scaleZ->setValue(1);

    vb1=new QVBoxLayout;
    lineEdit1=new QLineEdit(text);

    vb1->addWidget(lineEdit1);
    vb1->addWidget(translateX);
    vb1->addWidget(translateY);
    vb1->addWidget(translateZ);

    vb1->addWidget(rotateX);
    vb1->addWidget(rotateY);
    vb1->addWidget(rotateZ);

    vb1->addWidget(scaleX);
    vb1->addWidget(scaleY);
    vb1->addWidget(scaleZ);

    vb1->addWidget(btn1);

    setLayout(vb1);

    connect(translateX,SIGNAL(valueChanged(double)),this,SLOT(valueChanged()));
    connect(translateY,SIGNAL(valueChanged(double)),this,SLOT(valueChanged()));
    connect(translateZ,SIGNAL(valueChanged(double)),this,SLOT(valueChanged()));

    connect(rotateX,SIGNAL(valueChanged(double)),this,SLOT(valueChanged()));
    connect(rotateY,SIGNAL(valueChanged(double)),this,SLOT(valueChanged()));
    connect(rotateZ,SIGNAL(valueChanged(double)),this,SLOT(valueChanged()));

    connect(scaleX,SIGNAL(valueChanged(double)),this,SLOT(valueChanged()));
    connect(scaleY,SIGNAL(valueChanged(double)),this,SLOT(valueChanged()));
    connect(scaleZ,SIGNAL(valueChanged(double)),this,SLOT(valueChanged()));

    connect(lineEdit1,SIGNAL(textChanged(const QString&)),this,SLOT(textChangedSlot(const QString&)));

    connect(btn1,SIGNAL(clicked()),this,SLOT(btn1Clicked()));
    connect(colorDialog,SIGNAL(colorSelected(const QColor&)),this,SLOT(colorChanged(const QColor&)));
}

ModelPropertiesWidget::~ModelPropertiesWidget(){
    delete model;
}


void ModelPropertiesWidget::valueChanged(){
    glm::mat4 modelmat(1);
    modelmat=glm::translate(modelmat,glm::vec3(translateX->getValue(),translateY->getValue(),translateZ->getValue()));

    modelmat=glm::rotate(modelmat,(float)rotateX->getValue(),glm::vec3(1,0,0));
    modelmat=glm::rotate(modelmat,(float)rotateY->getValue(),glm::vec3(0,1,0));
    modelmat=glm::rotate(modelmat,(float)rotateZ->getValue(),glm::vec3(0,0,1));

    modelmat=glm::scale(modelmat,glm::vec3(scaleX->getValue(),scaleY->getValue(),scaleZ->getValue()));

    model->setModelMatrix(modelmat);
}

void ModelPropertiesWidget::setText(QString text){
    lineEdit1->setText(text);
    textChangedSlot(text);
}

void ModelPropertiesWidget::textChangedSlot(const QString& text){
    item->setText(text);
}

void ModelPropertiesWidget::btn1Clicked(){
    colorDialog->open();
}

void ModelPropertiesWidget::colorChanged(const QColor& color){
    model->setColor(color);
}
