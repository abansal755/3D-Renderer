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
    SliderFloat*slider1,*slider2,*slider3;
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
    double getAmbientLightIntensity(){return slider1->getValue();}
    double getDiffuseLightIntensity(){return slider2->getValue();}
    QColor getGridColor(){return gridColorDialog->currentColor();}
    double getGridSideLength(){return slider3->getValue();}
    bool isChangeInGrid();
    int getGridNumLines(){return slider4->getValue();}
    bool isShowGridChecked(){return chb1->checkState()==Qt::Checked;}
};
