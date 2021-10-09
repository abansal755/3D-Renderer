#include <QDialog>

class AboutDialog : public QDialog{
    Q_OBJECT
private slots:
    void openLinkedIn();
    void openGithub();
public:
    AboutDialog(QWidget*parent);
};
