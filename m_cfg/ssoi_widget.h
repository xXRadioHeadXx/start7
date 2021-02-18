#ifndef ssoi_widget_H
#define ssoi_widget_H

#include <QWidget>
#include <QMap>
#include <QErrorMessage>

namespace Ui {
class ssoi_widget;
}

class ssoi_widget : public QWidget
{
    Q_OBJECT

public:
    explicit ssoi_widget(QWidget *parent = nullptr);
    ~ssoi_widget();

    int  getPort() const;
    void setPort(int value);

    int  getBlinking() const;
    void setBlinking(int value);


void default_options();


void set_Version(int val);
int get_Version();

void set_SsoiM_PortNum1(int val);
int get_SsoiM_PortNum1();

void set_SsoiM_Interval1(int val);
int get_SsoiM_Interval1();

void set_SsoiM_Interval_1(int val);
int get_SsoiM_Interval_1();

void set_SsoiM_MaxErrCnt1(int val);
int get_SsoiM_MaxErrCnt1();

void set_SsoiM_PortNum2(int val);
int get_SsoiM_PortNum2();

void set_SsoiM_Interval2(int val);
int get_SsoiM_Interval2();

void set_SsoiM_Interval_2(int val);
int get_SsoiM_Interval_2();

void set_SsoiM_MaxErrCnt2(int val);
int get_SsoiM_MaxErrCnt2();

void set_SsoiM_PortNum3(int val);
int get_SsoiM_PortNum3();

void set_SsoiM_Interval3(int val);
int get_SsoiM_Interval3();

void set_SsoiM_Interval_3(int val);
int get_SsoiM_Interval_3();

void set_SsoiM_MaxErrCnt3(int val);
int get_SsoiM_MaxErrCnt3();

void set_SsoiM_PortNum4(int val);
int get_SsoiM_PortNum4();

void set_SsoiM_Interval4(int val);
int get_SsoiM_Interval4();

void set_SsoiM_Interval_4(int val);
int get_SsoiM_Interval_4();

void set_SsoiM_MaxErrCnt4(int val);
int get_SsoiM_MaxErrCnt4();

void set_SsoiAutoDkUse(int val);
int get_SsoiAutoDkUse();

void set_SsoiMOprosVariant(int val);
int get_SsoiMOprosVariant();


void set_SsoiFixNewWarning(int val);
int get_SsoiFixNewWarning();



int get_SsoiM_PortSpeed() const;
void set_SsoiM_PortSpeed(int value);

private slots:
void on_Version_currentIndexChanged(const QString &arg1);

    void on_SsoiMOprosVariant_currentIndexChanged(const QString &arg1);

private:

    Ui::ssoi_widget *ui;
    int SsoiM_PortSpeed=4800;
    QErrorMessage dialog;



     QMap <int,QString> l_Version;
     QString Version_1="ССОИ";
     QString Version_2="ССОИ-M";

     QMap <int,QString> l_SsoiAutoDkUse;
     QString SsoiAutoDkUse_0="ВЫКЛ";
     QString SsoiAutoDkUse_1="ВКЛ";

     QMap <int,QString> l_SsoiMOprosVariant;
     QString SsoiMOprosVariant_0="ССОИ-М";
     QString SsoiMOprosVariant_1="Адаптивный - БЛ";
     QString SsoiMOprosVariant_2="Адаптивный - БЛ2020";


};

#endif // ssoi_widget_H
