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

    float getRadius(){return slider1->getValue();}
    void setRadius(float val){slider1->setValue(val);}
    int getNumLines(){return slider2->getValue();}
    void setNumLines(int val){slider2->setValue(val);}
};
