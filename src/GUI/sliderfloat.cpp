#include "sliderfloat.h"

SliderFloat::SliderFloat(QString text,QWidget*parent=NULL,int minVal=0,int maxVal=100,int divisor=100)
    :minVal(minVal),maxVal(maxVal),divisor(divisor),QWidget(parent)
{
    label=new QLabel(text);
    slider=new QSlider(Qt::Horizontal);
    db1=new QDoubleSpinBox;
    hb1=new QHBoxLayout;

    hb1->addWidget(label);
    hb1->addWidget(slider);
    hb1->addWidget(db1);
    hb1->setContentsMargins(0,5,0,5);
    setLayout(hb1);

    slider->setMinimum(minVal);
    slider->setMaximum(maxVal);
    slider->setValue(minVal);
    db1->setDisabled(true);
    db1->setMinimum((double)minVal/divisor);
    db1->setMaximum((double)maxVal/divisor);
    db1->setSingleStep((double)1/divisor);
    db1->setValue((double)minVal/divisor);

    db1->setMaximumWidth(60);

    connect(slider,SIGNAL(valueChanged(int)),this,SLOT(valueChanged(int)));

    db1->setButtonSymbols(QAbstractSpinBox::NoButtons);
}

void SliderFloat::setValue(double val){
    slider->setValue(val*divisor);
    db1->setValue(val);
}
