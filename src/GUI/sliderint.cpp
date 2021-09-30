#include "sliderint.h"

SliderInt::SliderInt(QString text,QWidget*parent=NULL,int minVal=0,int maxVal=1)
    :minVal(minVal),maxVal(maxVal),QWidget(parent)
{
    label=new QLabel(text);
    slider=new QSlider(Qt::Horizontal);
    sb1=new QSpinBox;
    hb1=new QHBoxLayout;

    hb1->addWidget(label);
    hb1->addWidget(slider);
    hb1->addWidget(sb1);
    setLayout(hb1);

    slider->setMinimum(minVal);
    slider->setMaximum(maxVal);
    slider->setValue(minVal);
    sb1->setDisabled(true);
    sb1->setMinimum(minVal);
    sb1->setMaximum(maxVal);
    sb1->setValue(minVal);

    sb1->setMaximumWidth(60);

    connect(slider,SIGNAL(valueChanged(int)),this,SLOT(valueChangedSlot(int)));
}

void SliderInt::setValue(int val){
    slider->setValue(val);
    sb1->setValue(val);
}
