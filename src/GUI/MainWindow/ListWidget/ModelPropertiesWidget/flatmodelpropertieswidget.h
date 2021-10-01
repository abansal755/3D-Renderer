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

    QLineEdit*lineEdit1;
    QCheckBox*chb1;

    QColorDialog*colorDialog;
private slots:
    void valueChanged();
    void textChangedSlot(const QString& text);
    void btn1Clicked();
    void colorChanged(const QColor& color);
    void btn2Clicked();
public:
    FlatModelPropertiesWidget(FlatModelListWidgetItem*item,QString text);

    void setText(QString text);
    QString getText(){return lineEdit1->text();}
    virtual bool isVisible(){return (chb1->checkState()==Qt::Checked);}
};
