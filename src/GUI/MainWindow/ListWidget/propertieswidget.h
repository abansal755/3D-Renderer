#pragma once

#include <QWidget>
#include <QLineEdit>

class ListWidgetItem;

class PropertiesWidget : public QWidget{
    Q_OBJECT
    ListWidgetItem*item;
    QLineEdit*edit1;
    QWidget*container;
private slots:
    void textChangedSlot(const QString& text);
public:
    PropertiesWidget(ListWidgetItem*item,QString text);

    QWidget* getContainer(){return container;}
};
