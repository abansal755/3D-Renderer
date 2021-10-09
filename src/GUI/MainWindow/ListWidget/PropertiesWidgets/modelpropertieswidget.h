#include "src/OpenGL/model.h"
#include "../propertieswidget.h"

class ModelListWidgetItem;

class ModelPropertiesWidget : public PropertiesWidget{
    Model*model;
public:
    ModelPropertiesWidget(ModelListWidgetItem*item,QString text);
    virtual ~ModelPropertiesWidget();

    Model* getModel(){return model;}
};
