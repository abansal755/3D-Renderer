#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QColorDialog>
#include <QPushButton>

class SliderFloat;
class Model;
class Mesh;
class ListWidgetItem;

class ModelPropertiesWidget : public QWidget{
    Q_OBJECT
    ListWidgetItem*item;

    Model*model;

    SliderFloat*translateX,*translateY,*translateZ;
    SliderFloat*rotateX,*rotateY,*rotateZ;
    SliderFloat*scaleX,*scaleY,*scaleZ;

    QVBoxLayout*vb1;
    QLineEdit*lineEdit1;

    QColorDialog*colorDialog;
    QPushButton*btn1;
private slots:
    void valueChanged();
    void textChangedSlot(const QString& text);
    void btn1Clicked();
    void colorChanged(const QColor& color);
public:
    ModelPropertiesWidget(ListWidgetItem*item,QString text);
    ~ModelPropertiesWidget();

    void setModel(Model*model){this->model=model;}
    Model* getModel(){return model;}
    void setText(QString text);
    QString getText(){return lineEdit1->text();}
};
