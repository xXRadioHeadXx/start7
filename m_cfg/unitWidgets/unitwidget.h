#ifndef UNITWIDGET_H
#define UNITWIDGET_H

#include <QWidget>
#include <UnitNode.h>
#include <my_config.h>


namespace Ui {
class UnitWidget;
}

class UnitWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UnitWidget(QWidget *parent = nullptr);
    ~UnitWidget();

    int getID();


    virtual void get_option(UnitNode* unit);
    virtual void set_option(UnitNode* unit);

    virtual void update_name(){};
    virtual void setEnabled(bool){};
    virtual QString get_string(UnitNode* unit){return "";};

protected:
int ID;
//MainWindowCFG* wnd;


private:
    Ui::UnitWidget *ui;

signals:
    void updateName(QString);

};

#endif // UNITWIDGET_H
