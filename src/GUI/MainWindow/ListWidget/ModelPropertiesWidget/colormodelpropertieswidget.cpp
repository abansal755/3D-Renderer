#include "colormodelpropertieswidget.h"
#include "src/OpenGL/Models/colormodel.h"
#include "src/GUI/sliderfloat.h"
#include "lib/glm/gtc/matrix_transform.hpp"
#include "src/GUI/MainWindow/ListWidget/ListWidgetItem/colormodellistwidgetitem.h"

ColorModelPropertiesWidget::ColorModelPropertiesWidget(ColorModelListWidgetItem*item,QString text)
    :ModelPropertiesWidget((ListWidgetItem*)item,text)
{
    setModel(new ColorModel());
    ColorModel*model=(ColorModel*)getModel();

    colorDialog=new QColorDialog(model->getColor(),this);
    colorDialog->setOptions(QColorDialog::ShowAlphaChannel|QColorDialog::NoButtons);
    connect(colorDialog,SIGNAL(currentColorChanged(const QColor&)),this,SLOT(colorChanged(const QColor&)));

    QVBoxLayout*vb1=new QVBoxLayout;
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

        scaleUniform=new SliderFloat("scaleUniform",NULL,-500,500,100);
            scaleUniform->setValue(1);
            connect(scaleUniform,SIGNAL(valueChanged(double)),this,SLOT(valueChanged()));
        vb1->addWidget(scaleUniform);

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

        nestedContainer=new QWidget;
        vb1->addWidget(nestedContainer);

        QPushButton*btn1=new QPushButton("Change Color");
            connect(btn1,SIGNAL(clicked()),this,SLOT(btn1Clicked()));
        vb1->addWidget(btn1);

        QPushButton*btn2=new QPushButton("Delete");
            connect(btn2,SIGNAL(clicked()),this,SLOT(btn2Clicked()));
        vb1->addWidget(btn2);
    getContainer()->setLayout(vb1);
}

void ColorModelPropertiesWidget::valueChanged(){
    glm::mat4 modelmat(1);
    modelmat=glm::translate(modelmat,glm::vec3(translateX->getValue(),translateY->getValue(),translateZ->getValue()));

    modelmat=glm::rotate(modelmat,(float)rotateX->getValue(),glm::vec3(1,0,0));
    modelmat=glm::rotate(modelmat,(float)rotateY->getValue(),glm::vec3(0,1,0));
    modelmat=glm::rotate(modelmat,(float)rotateZ->getValue(),glm::vec3(0,0,1));

    modelmat=glm::scale(modelmat,glm::vec3(scaleX->getValue(),scaleY->getValue(),scaleZ->getValue()));

    modelmat=glm::scale(modelmat,glm::vec3(scaleUniform->getValue(),scaleUniform->getValue(),scaleUniform->getValue()));

    getModel()->setModelMatrix(modelmat);
}

void ColorModelPropertiesWidget::btn1Clicked(){
    colorDialog->open();
}

void ColorModelPropertiesWidget::colorChanged(const QColor& color){
    ColorModel*model=(ColorModel*)getModel();
    model->setColor(color);
}

void ColorModelPropertiesWidget::btn2Clicked(){
    QListWidget*listWidget=getItem()->listWidget();
    int row=listWidget->row(getItem());
    listWidget->takeItem(row);
    delete getItem();
}
