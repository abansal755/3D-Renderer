#include <QWidget>
#include <QColorDialog>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QCheckBox>

#include "sliderfloat.h"
#include "sliderint.h"

class SettingsWidget : public QWidget{
    Q_OBJECT
    QColorDialog*bgColorDialog,*lightColorDialog,*gridColorDialog;
    SliderFloat*slider1,*slider2,*slider3,*slider5,*slider6,*slider7,
    *slider8,*slider9;
    SliderInt*slider4;
    QCheckBox*chb1;

    bool changeInGrid=true;
private slots:
    void btn1Clicked();
    void btn2Clicked();
    void btn3Clicked();
    void gridChanged();
public:
    SettingsWidget(QWidget*parent=NULL);

    QColor getBGColor(){return bgColorDialog->currentColor();}
    QColor getLightColor(){return lightColorDialog->currentColor();}
    float getAmbientLightIntensity(){return slider1->getValue();}
    float getDiffuseLightIntensity(){return slider2->getValue();}
    QColor getGridColor(){return gridColorDialog->currentColor();}
    float getGridSideLength(){return slider3->getValue();}
    bool isChangeInGrid();
    int getGridNumLines(){return slider4->getValue();}
    bool isShowGridChecked(){return chb1->checkState()==Qt::Checked;}
    float getCameraMoveSpeed(){return slider5->getValue();}
    float getCameraTurnSpeed(){return slider6->getValue();}
    float getCameraFOV(){return slider7->getValue();}
    float getCameraZNear(){return slider8->getValue();}
    float getCameraZFar(){return slider9->getValue();}
};
