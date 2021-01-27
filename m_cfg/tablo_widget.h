#ifndef TABLO_WIDGET_H
#define TABLO_WIDGET_H

#include <QWidget>

namespace Ui {
class TABLO_Widget;
}

class TABLO_Widget : public QWidget
{
    Q_OBJECT



public:
    explicit TABLO_Widget(QWidget *parent = nullptr);
    ~TABLO_Widget();

    int  getPort() const;
    void setPort(int value);

    int  getBlinking() const;
    void setBlinking(int value);

    void default_options();

private:
    Ui::TABLO_Widget *ui;
    int Port;
    int Blinking;
};

#endif // TABLO_WIDGET_H
