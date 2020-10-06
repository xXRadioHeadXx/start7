#ifndef MYTREEVIEW_H
#define MYTREEVIEW_H

#include <QObject>
#include <QTreeView>



class MyTreeView : public QTreeView {

  Q_OBJECT

  public:
    MyTreeView(QWidget *parent = 0);

protected:

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;



};

#endif // MYTREEVIEW_H
