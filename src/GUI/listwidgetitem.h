#include <QListWidgetItem>

class ModelPropertiesWidget;
class Mesh;

class ListWidgetItem : public QListWidgetItem{
    ModelPropertiesWidget*widget;
public:
    ListWidgetItem();
    ~ListWidgetItem();

    ModelPropertiesWidget* getModelPropertiesWidget(){return widget;}
};
