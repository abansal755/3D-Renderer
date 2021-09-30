#include <QWidget>
#include <QColorDialog>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

#include "sliderfloat.h"

class SettingsWidget : public QWidget{
    Q_OBJECT
    QColorDialog*bgColorDialog,*lightColorDialog;
    SliderFloat*slider1,*slider2;
private slots:
    void btn1Clicked();
    void btn2Clicked();
public:
    SettingsWidget(QWidget*parent=NULL);

    QColor getBGColor(){return bgColorDialog->currentColor();}
    QColor getLightColor(){return lightColorDialog->currentColor();}
    double getAmbientLightIntensity(){return slider1->getValue();}
    double getDiffuseLightIntensity(){return slider2->getValue();}
};
