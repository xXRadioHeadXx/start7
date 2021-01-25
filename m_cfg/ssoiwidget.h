#ifndef SSOIWIDGET_H
#define SSOIWIDGET_H

#include <QWidget>
#include <QMap>

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

private slots:
    void on_Version_currentIndexChanged(const QString &arg1);

    void on_SsoiMOprosVariant_currentIndexChanged(const QString &arg1);

private:
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
