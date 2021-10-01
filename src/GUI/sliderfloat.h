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

    int minVal,maxVal,divisor;
signals:
    void valueChanged(double val);
private slots:
    void valueChanged(int val){
        double newVal=(double)val/divisor;
        db1->setValue(newVal);
        emit valueChanged(newVal);
    }
public:
    SliderFloat(QString text,QWidget*parent,int minVal,int maxVal,int divisor);

    void setText(QString text){label->setText(text);}
    QString getText(){return label->text();}
    void setValue(double val);
    double getValue(){return db1->value();}
    void setDecimals(int numDecimals){db1->setDecimals(numDecimals);}
    int decimals(){return db1->decimals();}
    void setSpinBoxWidth(int width){db1->setMaximumWidth(width);}
    int spinBoxWidth(){return db1->maximumWidth();}
};
