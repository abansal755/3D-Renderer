#include "src/GUI/MainWindow/ListWidget/modelpropertieswidget.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QColorDialog>
#include <QPushButton>
#include <QCheckBox>

class ColorModelListWidgetItem;
class SliderFloat;
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
};
