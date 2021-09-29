#include <QDialog>
#include <QColorDialog>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

class SettingsDialog : public QDialog{
    Q_OBJECT
    QColorDialog*bgColorDialog;
    QPushButton* btn1;
    QHBoxLayout*hb[1];
    QVBoxLayout*vb1;
    QLabel*label[1];
private slots:
    void btn1Clicked();
public:
    SettingsDialog(QWidget*parent=NULL);

    QColor getColor(){return bgColorDialog->currentColor();}
};
