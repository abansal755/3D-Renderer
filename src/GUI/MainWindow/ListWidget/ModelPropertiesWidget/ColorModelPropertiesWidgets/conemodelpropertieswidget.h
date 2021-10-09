#include "../colormodelpropertieswidget.h"
#include "src/GUI/sliderfloat.h"
#include "src/GUI/sliderint.h"

class ConeModelListWidgetItem;
class GLWidget;

class ConeModelPropertiesWidget : public ColorModelPropertiesWidget{
    Q_OBJECT
    GLWidget*glwidget;
    SliderFloat*slider1,*slider2;
    SliderInt*slider3;
private slots:
    void updateMesh();
public:
    ConeModelPropertiesWidget(ConeModelListWidgetItem*item,GLWidget*glwidget,QString text);
    ~ConeModelPropertiesWidget();
};
