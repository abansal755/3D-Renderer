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

    float getRadius(){return slider1->getValue();}
    void setRadius(float val){slider1->setValue(val);}
    float getHeight(){return slider2->getValue();}
    void setHeight(float val){slider2->setValue(val);}
    int getNumLines(){return slider3->getValue();}
    void setNumLines(int val){slider3->setValue(val);}
};
