#include "ListWidget/listwidgetitem.h"

#include <QListWidget>
#include <QVBoxLayout>

class ListWidget : public QListWidget{
    Q_OBJECT
    QVBoxLayout*layout;
private slots:
    void currentItemChangedSlot(QListWidgetItem*currPtr,
                            QListWidgetItem*prevPtr);
public:
    ListWidget(QVBoxLayout*layout,QWidget*parent=NULL);

    ListWidgetItem* getCustomCurrentItem(){return (ListWidgetItem*)currentItem();}
    ListWidgetItem* getCustomItem(int row){return (ListWidgetItem*)item(row);}
};
