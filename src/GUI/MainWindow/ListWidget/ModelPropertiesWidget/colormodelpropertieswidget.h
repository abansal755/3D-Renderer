#include "src/GUI/MainWindow/ListWidget/modelpropertieswidget.h"
#include "src/GUI/sliderfloat.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QColorDialog>
#include <QPushButton>
#include <QCheckBox>

class ColorModelListWidgetItem;
class FlatModel;
class Mesh;

class ColorModelPropertiesWidget : public ModelPropertiesWidget{
    Q_OBJECT

    SliderFloat*translateX,*translateY,*translateZ;
    SliderFloat*rotateX,*rotateY,*rotateZ;
    SliderFloat*scaleX,*scaleY,*scaleZ;
    SliderFloat*scaleUniform;

    QColorDialog*colorDialog;
    QWidget*nestedContainer;
private slots:
    void valueChanged();
    void btn1Clicked();
    void colorChanged(const QColor& color);
    void btn2Clicked();
protected:
    QWidget* getNestedContainer(){return nestedContainer;};
public:
    ColorModelPropertiesWidget(ColorModelListWidgetItem*item,QString text);

    float getTranslateX(){return translateX->getValue();}
    void setTranslateX(float val){translateX->setValue(val);}
    float getTranslateY(){return translateY->getValue();}
    void setTranslateY(float val){translateY->setValue(val);}
    float getTranslateZ(){return translateZ->getValue();}
    void setTranslateZ(float val){translateZ->setValue(val);}

    float getRotateX(){return rotateX->getValue();}
    void setRotateX(float val){rotateX->setValue(val);}
    float getRotateY(){return rotateY->getValue();}
    void setRotateY(float val){rotateY->setValue(val);}
    float getRotateZ(){return rotateZ->getValue();}
    void setRotateZ(float val){rotateZ->setValue(val);}

    float getScaleX(){return scaleX->getValue();}
    void setScaleX(float val){scaleX->setValue(val);}
    float getScaleY(){return scaleY->getValue();}
    void setScaleY(float val){scaleY->setValue(val);}
    float getScaleZ(){return scaleZ->getValue();}
    void setScaleZ(float val){scaleZ->setValue(val);}
    float getScaleUniform(){return scaleUniform->getValue();}
    void setScaleUniform(float val){scaleUniform->setValue(val);}
};
