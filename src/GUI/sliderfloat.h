#include <QWidget>
#include <QSlider>
#include <QLabel>
#include <QHBoxLayout>
#include <QDoubleSpinBox>

class SliderFloat : public QWidget{
    Q_OBJECT
    QLabel*label;
    QSlider*slider;
    QDoubleSpinBox*db1;
    QHBoxLayout*hb1;

    int minVal,maxVal,steps;
signals:
    void valueChanged(double val);
private slots:
    void valueChanged(int val){
        double newVal=(double)val/steps;
        db1->setValue(newVal);
        emit valueChanged(newVal);
    }
public:
    SliderFloat(QString text,QWidget*parent,int minVal,int maxVal,int steps);

    void setText(QString text){label->setText(text);}
    QString getText(){return label->text();}
    void setValue(double val);
    double getValue(){return db1->value();}
};
