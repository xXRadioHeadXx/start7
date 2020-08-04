#include "AuthenticationDialog.h"
#include "ui_AuthenticationDialog.h"

#include <QSettings>
#include <QDebug>
#include <Utils.h>
#include <QTextCodec>

AuthenticationDialog::AuthenticationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AuthenticationDialog)
{
    ui->setupUi(this);
    this->setResult(QDialog::Rejected);
    initialForm();
}

AuthenticationDialog::~AuthenticationDialog()
{
    delete ui;
}

Operator AuthenticationDialog::getApprovedOperator() const
{
    return approvedOperator;
}

void AuthenticationDialog::setApprovedOperator(const Operator &value)
{
    approvedOperator = value;
}

void AuthenticationDialog::initialForm(const QString fileName)
{
    QSettings settings(fileName, QSettings::IniFormat);
    settings.setIniCodec( "Windows-1251" );

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

    ui->comboBox->clear();
    for(int i = 0; i < listUser.size(); i++) {
        QString str;
        if(!listUser.at(i).FN.isEmpty()) {
            str.append(listUser.at(i).FN);
        }
        if(!listUser.at(i).N1.isEmpty()) {
            str.append(" " + listUser.at(i).N1);
        }
        if(!listUser.at(i).N2.isEmpty()) {
            str.append(" " + listUser.at(i).N2);
        }
        ui->comboBox->addItem(str);
    }
}

void AuthenticationDialog::on_pushButton_clicked()
{
    QString in = ui->lineEdit->text();
    QString key = "start7";

    QString crPW = Utils::XOR_Crypt(in,  key);
    QString PW = listUser.at(ui->comboBox->currentIndex()).PW;

    if(PW == crPW) {
        setApprovedOperator(listUser.at(ui->comboBox->currentIndex()));
        this->setResult(QDialog::Accepted);
        this->accept();
    } else {
        this->setResult(QDialog::Rejected);
        this->reject();
    }
}
