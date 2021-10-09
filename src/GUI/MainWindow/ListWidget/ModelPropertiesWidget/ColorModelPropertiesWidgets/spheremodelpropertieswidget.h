#include "../colormodelpropertieswidget.h"
#include "src/GUI/sliderfloat.h"
#include "src/GUI/sliderint.h"

class SphereModelListWidgetItem;
class GLWidget;

class SphereModelPropertiesWidget : public ColorModelPropertiesWidget{
    Q_OBJECT
    GLWidget*glwidget;
    SliderFloat*slider1;
    SliderInt*slider2;
private slots:
    void updateMesh();
public:
    SphereModelPropertiesWidget(SphereModelListWidgetItem*item,GLWidget*glwidget,QString text);
    ~SphereModelPropertiesWidget();
};
