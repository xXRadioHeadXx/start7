#ifndef SSOIWIDGET_H
#define SSOIWIDGET_H

#include <QWidget>
#include <QMap>
#include <QErrorMessage>

namespace Ui {
class SSOIwidget;
}

class SSOIwidget : public QWidget
{
    Q_OBJECT

public:
    explicit SSOIwidget(QWidget *parent = nullptr);
    ~SSOIwidget();



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

void set_SsoiM_PortSpeed(int val);
int get_SsoiM_PortSpeed();



private slots:
    void on_Version_currentIndexChanged(const QString &arg1);

    void on_SsoiMOprosVariant_currentIndexChanged(const QString &arg1);

private:

    QErrorMessage dialog;

    Ui::SSOIwidget *ui;

     QMap <int,QString> l_Version;
     QString Version_1="ССОИ";
     QString Version_2="ССОИ-M";

     QMap <int,QString> l_SsoiAutoDkUse;
     QString SsoiAutoDkUse_0="ВЫКЛ";
     QString SsoiAutoDkUse_1="ВКЛ";

     QMap <int,QString> l_SsoiMOprosVariant;
     QString SsoiMOprosVariant_0="ССОИ-М";
     QString SsoiMOprosVariant_1="Адаптивный опрос - БЛ";
     QString SsoiMOprosVariant_2="Адаптивный опрос - БЛ2020";


};

#endif // SSOIWIDGET_H
