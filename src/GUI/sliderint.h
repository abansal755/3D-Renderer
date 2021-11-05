#pragma once

#include <QWidget>
#include <QSlider>
#include <QLabel>
#include <QHBoxLayout>
#include <QSpinBox>

class SliderInt : public QWidget{
    Q_OBJECT
    QLabel*label;
    QSlider*slider;
    QSpinBox*sb1;
    QHBoxLayout*hb1;

    int minVal,maxVal;
signals:
    void valueChanged(int val);
private slots:
    void valueChangedSlot(int val){
        sb1->setValue(val);
        emit valueChanged(val);
    }
public:
    SliderInt(QString text,QWidget*parent,int minVal,int maxVal);

    void setText(QString text){label->setText(text);}
    QString getText(){return label->text();}
    void setValue(int val);
    int getValue(){return sb1->value();}
};
