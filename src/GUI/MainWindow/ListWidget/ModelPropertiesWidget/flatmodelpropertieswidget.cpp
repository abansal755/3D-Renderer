#include "flatmodelpropertieswidget.h"
#include "src/OpenGL/Models/flatmodel.h"
#include "src/GUI/sliderfloat.h"
#include "lib/glm/gtc/matrix_transform.hpp"
#include "src/GUI/MainWindow/ListWidget/ListWidgetItem/flatmodellistwidgetitem.h"

FlatModelPropertiesWidget::FlatModelPropertiesWidget(FlatModelListWidgetItem*item,QString text)
    :ModelPropertiesWidget((ListWidgetItem*)item)
{
    setModel(new FlatModel());
    FlatModel*model=(FlatModel*)getModel();

    colorDialog=new QColorDialog(model->getColor(),this);
    colorDialog->setOptions(QColorDialog::ShowAlphaChannel|QColorDialog::NoButtons);
    connect(colorDialog,SIGNAL(currentColorChanged(const QColor&)),this,SLOT(colorChanged(const QColor&)));

    QVBoxLayout*vb1=new QVBoxLayout;
        lineEdit1=new QLineEdit(text);
            connect(lineEdit1,SIGNAL(textChanged(const QString&)),this,SLOT(textChangedSlot(const QString&)));
        vb1->addWidget(lineEdit1);
        chb1=new QCheckBox("Visible");
            chb1->setCheckState(Qt::Checked);
        vb1->addWidget(chb1);

        translateX=new SliderFloat("translateX",NULL,-500,500,100);
            translateX->setValue(0);
            connect(translateX,SIGNAL(valueChanged(double)),this,SLOT(valueChanged()));
        vb1->addWidget(translateX);

        translateY=new SliderFloat("translateY",NULL,-500,500,100);
            translateY->setValue(0);
            connect(translateY,SIGNAL(valueChanged(double)),this,SLOT(valueChanged()));
        vb1->addWidget(translateY);

        translateZ=new SliderFloat("translateZ",NULL,-500,500,100);
            translateZ->setValue(0);
            connect(translateZ,SIGNAL(valueChanged(double)),this,SLOT(valueChanged()));
        vb1->addWidget(translateZ);

        rotateX=new SliderFloat("rotateX",NULL,-500,500,100);
            rotateX->setValue(0);
            connect(rotateX,SIGNAL(valueChanged(double)),this,SLOT(valueChanged()));
        vb1->addWidget(rotateX);

        rotateY=new SliderFloat("rotateY",NULL,-500,500,100);
            rotateY->setValue(0);
            connect(rotateY,SIGNAL(valueChanged(double)),this,SLOT(valueChanged()));
        vb1->addWidget(rotateY);

        rotateZ=new SliderFloat("rotateZ",NULL,-500,500,100);
            rotateZ->setValue(0);
            connect(rotateZ,SIGNAL(valueChanged(double)),this,SLOT(valueChanged()));
        vb1->addWidget(rotateZ);

        scaleX=new SliderFloat("scaleX",NULL,-500,500,100);
            scaleX->setValue(1);
            connect(scaleX,SIGNAL(valueChanged(double)),this,SLOT(valueChanged()));
        vb1->addWidget(scaleX);

        scaleY=new SliderFloat("scaleY",NULL,-500,500,100);
            scaleY->setValue(1);
            connect(scaleY,SIGNAL(valueChanged(double)),this,SLOT(valueChanged()));
        vb1->addWidget(scaleY);

        scaleZ=new SliderFloat("scaleZ",NULL,-500,500,100);
            scaleZ->setValue(1);
            connect(scaleZ,SIGNAL(valueChanged(double)),this,SLOT(valueChanged()));
        vb1->addWidget(scaleZ);

        QPushButton*btn1=new QPushButton("Change Color");
            connect(btn1,SIGNAL(clicked()),this,SLOT(btn1Clicked()));
        vb1->addWidget(btn1);

        QPushButton*btn2=new QPushButton("Delete");
            connect(btn2,SIGNAL(clicked()),this,SLOT(btn2Clicked()));
        vb1->addWidget(btn2);
    setLayout(vb1);
}

void FlatModelPropertiesWidget::valueChanged(){
    glm::mat4 modelmat(1);
    modelmat=glm::translate(modelmat,glm::vec3(translateX->getValue(),translateY->getValue(),translateZ->getValue()));

    modelmat=glm::rotate(modelmat,(float)rotateX->getValue(),glm::vec3(1,0,0));
    modelmat=glm::rotate(modelmat,(float)rotateY->getValue(),glm::vec3(0,1,0));
    modelmat=glm::rotate(modelmat,(float)rotateZ->getValue(),glm::vec3(0,0,1));

    modelmat=glm::scale(modelmat,glm::vec3(scaleX->getValue(),scaleY->getValue(),scaleZ->getValue()));

    getModel()->setModelMatrix(modelmat);
}

void FlatModelPropertiesWidget::setText(QString text){
    lineEdit1->setText(text);
    textChangedSlot(text);
}

void FlatModelPropertiesWidget::textChangedSlot(const QString& text){
    getItem()->setText(text);
}

void FlatModelPropertiesWidget::btn1Clicked(){
    colorDialog->open();
}

void FlatModelPropertiesWidget::colorChanged(const QColor& color){
    FlatModel*model=(FlatModel*)getModel();
    model->setColor(color);
}

void FlatModelPropertiesWidget::btn2Clicked(){
    QListWidget*listWidget=getItem()->listWidget();
    int row=listWidget->row(getItem());
    listWidget->takeItem(row);
    delete getItem();
}
