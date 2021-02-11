#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <rif_widget_model.h>
#include <rif_widget_delegate.h>


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    rif_widget_model* model;



private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
