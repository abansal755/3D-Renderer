#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>

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
private slots:
    void valueChanged();
    void textChangeSlot(const QString& text);
public:
    ModelPropertiesWidget(ListWidgetItem*item,QString text);
    ~ModelPropertiesWidget();

    void setModel(Model*model){this->model=model;}
    Model* getModel(){return model;}
    void setText(QString text){lineEdit1->setText(text);}
    QString getText(){return lineEdit1->text();}
};
