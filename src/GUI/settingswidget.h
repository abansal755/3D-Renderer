#include <QWidget>
#include <QColorDialog>
#include <QGroupBox>
#include <QComboBox>
#include <QMessageBox>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QCheckBox>

#include "sliderfloat.h"
#include "sliderint.h"
#include "src/OpenGL/camera.h"

class SettingsWidget : public QWidget{
    Q_OBJECT
    QColorDialog*bgColorDialog,*lightColorDialog,*gridColorDialog;
    SliderFloat*slider1,*slider2,*slider3,*slider5,*slider6,*slider7,
    *slider8,*slider9;
    SliderInt*slider4;

    QGroupBox*box3;

    QComboBox*cb1;
    QCheckBox*cb2;

    QNetworkAccessManager*manager;

    bool changeInGrid=true;

    QJsonObject qColorToJson(QColor color,bool alpha=true);
    bool isColorJsonValid(QJsonObject json);
    QColor jsonToQColor(QJsonObject json);
    QJsonObject settingsToJson();
    void loadSettings();

    //default settings
    bool defaultUpdates=true;
    QColor defaultBGColor;
    int defaultVsync=1;
    QColor defaultLightColor;
    float defaultAmbientLightIntensity=0.25;
    float defaultDiffuseLightIntensity=1;
    QColor defaultGridColor;
    float defaultGridSideLength=5;
    int defaultGridNumLines=10;
    bool defaultIsShowGridChecked=true;
    float defaultCameraMoveSpeed=10;
    float defaultCameraTurnSpeed=0.005;
    float defaultCameraFOV=PI/4;
    float defaultCameraZNear=0.01;
    float defaultCameraZFar=100;
private slots:
    void btn1Clicked();
    void btn2Clicked();
    void btn3Clicked();
    void btn4Clicked();
    void cb1Changed();
    void gridChanged();

    void requestFinished(QNetworkReply*reply);
public slots:
    void checkForUpdates();
public:
    SettingsWidget(QWidget*parent=NULL);
    ~SettingsWidget();

    bool getUpdates(){return cb2->checkState()==Qt::Checked;}
    void setUpdates(bool val){
        if(val) cb2->setCheckState(Qt::Checked);
        else cb2->setCheckState(Qt::Unchecked);
    }
    QColor getBGColor(){return bgColorDialog->currentColor();}
    void setBGColor(QColor color){this->bgColorDialog->setCurrentColor(color);}
    int getVsyncMode(){return cb1->currentIndex();}
    void setVsyncMode(int value);
    QColor getLightColor(){return lightColorDialog->currentColor();}
    void setLightColor(QColor color){this->lightColorDialog->setCurrentColor(color);}
    float getAmbientLightIntensity(){return slider1->getValue();}
    void setAmbientLightIntensity(float value){slider1->setValue(value);}
    float getDiffuseLightIntensity(){return slider2->getValue();}
    void setDiffuseLightIntensity(float value){slider2->setValue(value);}
    QColor getGridColor(){return gridColorDialog->currentColor();}
    void setGridColor(QColor color){gridColorDialog->setCurrentColor(color);}
    float getGridSideLength(){return slider3->getValue();}
    void setGridSideLength(float value){slider3->setValue(value);}
    bool isChangeInGrid();
    int getGridNumLines(){return slider4->getValue();}
    void setGridNumLines(int value){slider4->setValue(value);}
    bool isShowGridChecked(){return box3->isChecked();}
    void setIsShowGridChecked(bool value){box3->setChecked(value);}
    float getCameraMoveSpeed(){return slider5->getValue();}
    void setCameraMoveSpeed(float value){slider5->setValue(value);}
    float getCameraTurnSpeed(){return slider6->getValue();}
    void setCameraTurnSpeed(float value){slider6->setValue(value);}
    float getCameraFOV(){return slider7->getValue();}
    void setCameraFOV(float value){slider7->setValue(value);}
    float getCameraZNear(){return slider8->getValue();}
    void setCameraZNear(float value){slider8->setValue(value);}
    float getCameraZFar(){return slider9->getValue();}
    void setCameraZFar(float value){slider9->setValue(value);}
};
