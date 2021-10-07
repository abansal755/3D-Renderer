#include "cylindermodelpropertieswidget.h"
#include "src/GUI/MainWindow/ListWidget/ListWidgetItem/cylindermodellistwidgetitem.h"
#include "src/GUI/MainWindow/glwidget.h"
#include "src/OpenGL/Models/colormodel.h"

CylinderModelPropertiesWidget::CylinderModelPropertiesWidget(CylinderModelListWidgetItem*item,
                                                     GLWidget*glwidget,QString text)
    :ColorModelPropertiesWidget((ColorModelListWidgetItem*)item,text),
      glwidget(glwidget)
{
    QWidget*container=getNestedContainer();
    QVBoxLayout*vb1=new QVBoxLayout;
        vb1->setContentsMargins(0,0,0,0);
        slider1=new SliderFloat("Radius",NULL,1,1000,100);
            float defaultRadius=0.5;
            slider1->setValue(defaultRadius);
            connect(slider1,SIGNAL(valueChanged(double)),this,SLOT(updateMesh()));
        vb1->addWidget(slider1);
        slider2=new SliderFloat("Height",NULL,1,1000,100);
            float defaultHeight=1;
            slider2->setValue(defaultHeight);
            connect(slider2,SIGNAL(valueChanged(double)),this,SLOT(updateMesh()));
        vb1->addWidget(slider2);
        slider3=new SliderInt("Number of lines",NULL,3,1000);
            int defaultNumLines=50;
            slider3->setValue(defaultNumLines);
            connect(slider3,SIGNAL(valueChanged(int)),this,SLOT(updateMesh()));
        vb1->addWidget(slider3);
    container->setLayout(vb1);
    updateMesh();
}

void CylinderModelPropertiesWidget::updateMesh(){
    ColorModel* model=(ColorModel*)getModel();
    if(model->getMesh()) delete model->getMesh();
    model->setMesh(glwidget->getCylinderMesh(slider1->getValue(),slider2->getValue(),slider3->getValue()));
}

CylinderModelPropertiesWidget::~CylinderModelPropertiesWidget(){
    delete getModel()->getMesh();
}
