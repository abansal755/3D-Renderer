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
    float getTranslateY(){return translateY->getValue();}
    float getTranslateZ(){return translateZ->getValue();}

    float getRotateX(){return rotateX->getValue();}
    float getRotateY(){return rotateY->getValue();}
    float getRotateZ(){return rotateZ->getValue();}

    float getScaleX(){return scaleX->getValue();}
    float getScaleY(){return scaleY->getValue();}
    float getScaleZ(){return scaleZ->getValue();}
    float getScaleUniform(){return scaleUniform->getValue();}
};
