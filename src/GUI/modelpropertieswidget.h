#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>

class SliderFloat;
class Model;
class Mesh;

class ModelPropertiesWidget : public QWidget{
    Q_OBJECT
    Model*model;

    SliderFloat*translateX,*translateY,*translateZ;
    SliderFloat*rotateX,*rotateY,*rotateZ;
    SliderFloat*scaleX,*scaleY,*scaleZ;

    QHBoxLayout*hb[3];
    QVBoxLayout*vb1;
private slots:
    void valueChanged();
public:
    ModelPropertiesWidget();
    ~ModelPropertiesWidget();

    void setModel(Model*model){this->model=model;}
    Model* getModel(){return model;}
};
