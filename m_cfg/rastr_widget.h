#ifndef RASTR_WIDGET_H
#define RASTR_WIDGET_H

#include <QWidget>
#include <QMap>
#include <QErrorMessage>
#include <my_config.h>

namespace Ui {
class RASTR_Widget;
}

class RASTR_Widget : public QWidget
{
    Q_OBJECT

public:
    explicit RASTR_Widget(QWidget *parent = nullptr);
    ~RASTR_Widget();


    QErrorMessage dialog;

    void default_options();



    int getUse() const;
    void setUse(int value);

    QString getName() const;
    void setName(const QString &value);

    int getPort() const;
    void setPort(int value);

    int getPort2() const;
    void setPort2(int value);

    int getKeepAliveInterval() const;
    void setKeepAliveInterval(int value);

    int getThermostatUse() const;
    void setThermostatUse(int value);

    int getDtInfoToJpg() const;
    void setDtInfoToJpg(int value);

    int getAutoDkPeriod() const;
    void setAutoDkPeriod(int value);

    int getRASTR__Port() const;
    void setRASTR__Port(int value);

    int getSOLID__Port() const;
    void setSOLID__Port(int value);

    void set_pointer(QMap <QString, SerNum_Name>* mSerNum_Name);
    void get_from_rastr_ini();

    QString getRASTRMSSOI__SerNum() const;
    void setRASTRMSSOI__SerNum(const QString &value);

    int getRASTRMSSOI__Speed() const;
    void setRASTRMSSOI__Speed(int value);

    int getRASTRMSSOI__Timeout() const;
    void setRASTRMSSOI__Timeout(int value);

    QString rastrmtv_cfg__path() const;

private slots:
    void on_Use_activated(const QString &arg1);

    void on_pushButton_clicked();

private:

    QMap <QString, SerNum_Name>* mSerNum_Name;

    Ui::RASTR_Widget *ui;
    
    //    [RASTRMTV]
    int Use=0;

    QMap <int,QString> l_Use;
    QString Use_0="Выкл";
    QString Use_1="РАСТР-М-ТВ";
    QString Use_2="Растр";

    QString Name="localhost";
    int Port=1972;
    int Port2=1974;

    int KeepAliveInterval=20;

    int ThermostatUse=0;
    int dtInfoToJpg=0;

    QMap <int,QString> l_ThermostatUse;
    QString ThermostatUse_0="Не использовать";
    QString ThermostatUse_1="Использовать";

    int AutoDkPeriod=10;

    QMap <int,QString> l_AutoDkPeriod;
    QString AutoDkPeriod_0="Постоянно";
    QString AutoDkPeriod_10="10 мин.";
    
//    [RASTR]
    int RASTR__Port=0;
    
//    [SOLID]
    int SOLID__Port=0;
    
//    [ADAM4068]
    int ADAM__Port=0;
    int ADAM__Interval=100;
            
//    [RASTRMSSOI]
    QString RASTRMSSOI__SerNum="";
    int RASTRMSSOI__Speed=0;
    int RASTRMSSOI__Timeout=50 ;           
};

#endif // RASTR_WIDGET_H
