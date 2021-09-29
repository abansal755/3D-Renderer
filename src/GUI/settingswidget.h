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
    QPushButton* btn[2];
    QHBoxLayout*hb[4];
    QVBoxLayout*vb1;
    QLabel*label[2];
    SliderFloat*slider[2];
private slots:
    void btn0Clicked();
    void btn1Clicked();
public:
    SettingsWidget(QWidget*parent=NULL);

    QColor getBGColor(){return bgColorDialog->currentColor();}
    QColor getLightColor(){return lightColorDialog->currentColor();}
    double getAmbientLightIntensity(){return slider[0]->getValue();}
    double getDiffuseLightIntensity(){return slider[1]->getValue();}
};
