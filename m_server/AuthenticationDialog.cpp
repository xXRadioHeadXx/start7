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
    setInitialResult(initialForm());
}

AuthenticationDialog::~AuthenticationDialog()
{
    delete ui;
}

int AuthenticationDialog::initialForm(const QString fileName)
{
    QSettings settings(fileName, QSettings::IniFormat);
    settings.setIniCodec( "Windows-1251" );

    if(!settings.childGroups().contains("OPERATORS")) {
        this->setResult(QDialog::Rejected);
        return 0;
    }

    settings.beginGroup("OPERATORS");
    if(!settings.childKeys().contains("Use")) {
        this->setResult(QDialog::Rejected);
        return 0;
    }
    if(0 == settings.value( "Use", -1 ).toInt()){
        this->setResult(QDialog::Accepted);
        return 0;
    }

    if(!settings.childKeys().contains("Count")) {
        this->setResult(QDialog::Rejected);
        return 0;
    }
    int userCount = settings.value( "Count", -1 ).toInt();
    settings.endGroup();

    if(0 == userCount){
        this->setResult(QDialog::Accepted);
        return 0;
    }

    listUser.clear();
    for(int i = 0; i < userCount; i++) {
        QString group = "Operator_%1";
        group = group.arg(i);
        settings.beginGroup(group);
        Operator newUser;
        newUser.setFN(settings.value( "FN", -1 ).toString());
        newUser.setN1(settings.value( "N1", -1 ).toString());
        newUser.setN2(settings.value( "N2", -1 ).toString());
        newUser.setPW(settings.value( "PW", -1 ).toString());
        settings.endGroup();
        listUser.append(newUser);
    }

    ui->comboBox->clear();
    for(int i = 0; i < listUser.size(); i++) {
        ui->comboBox->addItem(listUser.at(i).getOperatorLable());
    }
    return 1;
}

void AuthenticationDialog::on_pushButton_clicked()
{
    QString in = ui->lineEdit->text();
    QString key = "start7";

    QString crPW = Operator::XOR_Crypt(in,  key);
    QString PW = listUser.at(ui->comboBox->currentIndex()).getPW();

    if(PW == crPW) {
        Operator::setApprovedOperator(listUser.at(ui->comboBox->currentIndex()));
        this->setResult(QDialog::Accepted);
        this->accept();
    } else {
        this->setResult(QDialog::Rejected);
        this->reject();
    }
}

int AuthenticationDialog::getInitialResult() const
{
    return initialResult;
}

void AuthenticationDialog::setInitialResult(int value)
{
    initialResult = value;
}
