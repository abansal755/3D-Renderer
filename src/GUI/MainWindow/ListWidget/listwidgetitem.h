#include <QListWidgetItem>

class ModelPropertiesWidget;
class Mesh;

class ListWidgetItem : public QListWidgetItem{
    ModelPropertiesWidget*widget;
public:
    ListWidgetItem(QString text="Model");
    ~ListWidgetItem();

    ModelPropertiesWidget* getModelPropertiesWidget(){return widget;}
    void changeText(QString text);
    QString getText(){return text();}
};
