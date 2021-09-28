#include "modelpropertieswidget.h"
#include "src/OpenGL/model.h"
#include "lib/glm/gtc/matrix_transform.hpp"

#include <QDebug>

ModelPropertiesWidget::ModelPropertiesWidget(Model*model):model(model){
    translateX=new SliderFloat("translateX",NULL,-500,500,100);
    translateY=new SliderFloat("translateY",NULL,-500,500,100);
    translateZ=new SliderFloat("translateZ",NULL,-500,500,100);

    rotateX=new SliderFloat("rotateX",NULL,-500,500,100);
    rotateY=new SliderFloat("rotateY",NULL,-500,500,100);
    rotateZ=new SliderFloat("rotateZ",NULL,-500,500,100);

    scaleX=new SliderFloat("scaleX",NULL,-500,500,100);
    scaleY=new SliderFloat("scaleY",NULL,-500,500,100);
    scaleZ=new SliderFloat("scaleZ",NULL,-500,500,100);

    vb1=new QVBoxLayout;
    for(int i=0;i<3;i++){
        hb[i]=new QHBoxLayout;
        vb1->addLayout(hb[i]);
    }

    hb[0]->addWidget(translateX);
    hb[0]->addWidget(translateY);
    hb[0]->addWidget(translateZ);

    hb[1]->addWidget(rotateX);
    hb[1]->addWidget(rotateY);
    hb[1]->addWidget(rotateZ);

    hb[2]->addWidget(scaleX);
    hb[2]->addWidget(scaleY);
    hb[2]->addWidget(scaleZ);

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
