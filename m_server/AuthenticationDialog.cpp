#include "AuthenticationDialog.h"
#include "ui_AuthenticationDialog.h"

#include <QSettings>

AuthenticationDialog::AuthenticationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AuthenticationDialog)
{
    ui->setupUi(this);
}

AuthenticationDialog::~AuthenticationDialog()
{
    delete ui;
}

void AuthenticationDialog::initialForm(const QString fileName)
{
    QSettings settings(fileName, QSettings::IniFormat);

    if(!settings.childGroups().contains("OPERATORS")) {
        this->setResult(QDialog::Rejected);
        return;
    }

    settings.beginGroup("OPERATORS");
    if(!settings.childKeys().contains("Use")) {
        this->setResult(QDialog::Rejected);
        return;
    }
    if(0 == settings.value( "Use", -1 ).toInt()){
        this->setResult(QDialog::Accepted);
        return;
    }

    if(!settings.childKeys().contains("Count")) {
        this->setResult(QDialog::Rejected);
        return;
    }
    int userCount = settings.value( "Count", -1 ).toInt();
    settings.endGroup();

    if(0 == userCount){
        this->setResult(QDialog::Accepted);
        return;
    }

    listUser.clear();
    for(int i = 0; i < userCount; i++) {
        QString group = "Operator_%1";
        group = group.arg(i);
        settings.beginGroup(group);
        Operator newUser;
        newUser.FN = settings.value( "FN", -1 ).toString();
        newUser.N1 = settings.value( "N1", -1 ).toString();
        newUser.N2 = settings.value( "N2", -1 ).toString();
        newUser.PW = settings.value( "PW", -1 ).toString();
        settings.endGroup();
        listUser.append(newUser);
    }

    for(int i = 0; i < listUser.size(); i++) {

    }
}
