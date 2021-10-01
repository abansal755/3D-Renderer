#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QColorDialog>
#include <QPushButton>
#include <QCheckBox>

class SliderFloat;
class FlatModel;
class Mesh;
class ListWidgetItem;

class ModelPropertiesWidget : public QWidget{
    Q_OBJECT
    ListWidgetItem*item;

    FlatModel*model;

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
    ModelPropertiesWidget(ListWidgetItem*item,QString text);
    ~ModelPropertiesWidget();

    void setModel(FlatModel*model){this->model=model;}
    FlatModel* getModel(){return model;}
    void setText(QString text);
    QString getText(){return lineEdit1->text();}
    bool isVisible(){return (chb1->checkState()==Qt::Checked);}
};
