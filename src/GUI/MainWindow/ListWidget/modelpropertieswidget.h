#include <QWidget>
#include <QLineEdit>
#include <QCheckBox>

class ListWidgetItem;
class Model;

class ModelPropertiesWidget : public QWidget{
    Q_OBJECT
    ListWidgetItem*item;

    Model*model;

    QLineEdit*lineEdit1;
    QCheckBox*chb1;

    QWidget*container;
protected:
    ListWidgetItem* getItem(){return item;}
    QWidget* getContainer(){return container;}
private slots:
    void textChangedSlot(const QString& text);
public:
    ModelPropertiesWidget(ListWidgetItem*item,QString text);
    virtual ~ModelPropertiesWidget();

    void setModel(Model*model){this->model=model;}
    Model* getModel(){return model;}
    void setText(QString text);
    QString getText(){return lineEdit1->text();}
    bool isVisible(){return (chb1->checkState()==Qt::Checked);}
};
