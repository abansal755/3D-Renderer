#include "aboutdialog.h"
#include "qssloader.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QImage>
#include <QDebug>
#include <QPushButton>
#include <QDesktopServices>
#include <QUrl>

AboutDialog::AboutDialog(QWidget*parent):QDialog(parent){
    setWindowFlag(Qt::WindowContextHelpButtonHint,false);

    QHBoxLayout*hb1=new QHBoxLayout;
        QLabel*label1=new QLabel;
            QPixmap pixmap;
            pixmap.load(":/images/logo.png");
            pixmap=pixmap.scaled(pixmap.width()/2,pixmap.height()/2);
            label1->setPixmap(pixmap);
        hb1->addWidget(label1);
        QVBoxLayout*vb1=new QVBoxLayout;
            vb1->addStretch();
            QLabel*label2=new QLabel("3D Renderer v1.0.0");
                label2->setObjectName("app-name");
            vb1->addWidget(label2);
            QLabel*label3=new QLabel("Developed by Akshit Bansal");
                label3->setObjectName("dev-name");
            vb1->addWidget(label3);
            QHBoxLayout*hb2=new QHBoxLayout;
                hb2->addStretch();
                QPushButton*btn1=new QPushButton("LinkedIn");
                    connect(btn1,SIGNAL(clicked()),this,SLOT(openLinkedIn()));
                hb2->addWidget(btn1);
                QPushButton*btn2=new QPushButton("GitHub");
                    connect(btn2,SIGNAL(clicked()),this,SLOT(openGithub()));
                hb2->addWidget(btn2);
                hb2->addStretch();
            vb1->addLayout(hb2);
            vb1->addStretch();
        hb1->addLayout(vb1);
    setLayout(hb1);

    qssLoader(this,":/qss/aboutdialog.qss");

    adjustSize();
    setFixedSize(size());
}

void AboutDialog::openLinkedIn(){
    QDesktopServices::openUrl(QUrl("https://www.linkedin.com/in/abansal755/"));
}

void AboutDialog::openGithub(){
    QDesktopServices::openUrl(QUrl("https://github.com/abansal755"));
}
