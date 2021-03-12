#ifndef MY_TREEVIEW_H
#define MY_TREEVIEW_H

#include <QWidget>
#include <QTreeView>

class My_treeView : public QTreeView
{
    Q_OBJECT
public:
    explicit My_treeView(QWidget *parent = nullptr);
    
 void keyPressEvent ( QKeyEvent * event ) override;

signals:
 void new_current_index(QModelIndex);

};

#endif // MY_TREEVIEW_H
