#include "sliderfloat.h"

SliderFloat::SliderFloat(QString text,QWidget*parent=NULL,int minVal=0,int maxVal=1,int steps=100)
    :minVal(minVal),maxVal(maxVal),steps(steps),QWidget(parent)
{
    label=new QLabel(text);
    slider=new QSlider(Qt::Horizontal);
    db1=new QDoubleSpinBox;
    hb1=new QHBoxLayout;

    hb1->addWidget(label);
    hb1->addWidget(slider);
    hb1->addWidget(db1);
    setLayout(hb1);

    slider->setMinimum(minVal);
    slider->setMaximum(maxVal);
    slider->setValue(minVal);
    db1->setDisabled(true);
    db1->setMinimum((double)minVal/steps);
    db1->setMaximum((double)maxVal/steps);
    db1->setSingleStep((double)(maxVal-minVal)/steps);
    db1->setValue((double)minVal/steps);

    db1->setMaximumWidth(60);

    connect(slider,SIGNAL(valueChanged(int)),this,SLOT(valueChanged(int)));
}

void SliderFloat::setValue(double val){
    slider->setValue(val*steps);
    db1->setValue(val);
}
