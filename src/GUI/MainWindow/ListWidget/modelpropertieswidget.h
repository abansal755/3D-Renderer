#include <QWidget>

class ListWidgetItem;
class Model;

class ModelPropertiesWidget : public QWidget{
    Q_OBJECT
    ListWidgetItem*item;

    Model*model;
protected:
    ListWidgetItem* getItem(){return item;}
public:
    ModelPropertiesWidget(ListWidgetItem*item):item(item){};
    virtual ~ModelPropertiesWidget();

    void setModel(Model*model){this->model=model;}
    Model* getModel(){return model;}
    virtual bool isVisible()=0;
};
