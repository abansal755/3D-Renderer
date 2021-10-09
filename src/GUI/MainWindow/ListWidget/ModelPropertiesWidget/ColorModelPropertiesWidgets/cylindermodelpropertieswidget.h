#include "../colormodelpropertieswidget.h"
#include "src/GUI/sliderfloat.h"
#include "src/GUI/sliderint.h"

class CylinderModelListWidgetItem;
class GLWidget;

class CylinderModelPropertiesWidget : public ColorModelPropertiesWidget{
    Q_OBJECT
    GLWidget*glwidget;
    SliderFloat*slider1,*slider2;
    SliderInt*slider3;
private slots:
    void updateMesh();
public:
    CylinderModelPropertiesWidget(CylinderModelListWidgetItem*item,GLWidget*glwidget,QString text);
    ~CylinderModelPropertiesWidget();
};
