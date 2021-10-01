#include "src/GUI/MainWindow/ListWidget/modelpropertieswidget.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QColorDialog>
#include <QPushButton>
#include <QCheckBox>

class FlatModelListWidgetItem;
class SliderFloat;
class FlatModel;
class Mesh;

class FlatModelPropertiesWidget : public ModelPropertiesWidget{
    Q_OBJECT

    SliderFloat*translateX,*translateY,*translateZ;
    SliderFloat*rotateX,*rotateY,*rotateZ;
    SliderFloat*scaleX,*scaleY,*scaleZ;
    SliderFloat*scaleUniform;

    QColorDialog*colorDialog;
private slots:
    void valueChanged();
    void btn1Clicked();
    void colorChanged(const QColor& color);
    void btn2Clicked();
public:
    FlatModelPropertiesWidget(FlatModelListWidgetItem*item,QString text);
};
