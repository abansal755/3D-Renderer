#include <QListWidget>
#include <QVBoxLayout>

class ListWidgetItem;

class ListWidget : public QListWidget{
    Q_OBJECT
    QVBoxLayout*layout;
private slots:
    void currentItemChanged(QListWidgetItem*currPtr,QListWidgetItem*prevPtr);
public:
    ListWidget(QVBoxLayout*layout,QWidget*parent=NULL);

    ListWidgetItem* getCustomCurrentItem();
    ListWidgetItem* getCustomItem(int row);
};
