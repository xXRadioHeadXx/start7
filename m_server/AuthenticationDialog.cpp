#include "AuthenticationDialog.h"
#include "ui_AuthenticationDialog.h"

#include <QDebug>
#include "Utils.h"
#include <QTextCodec>
#include "Utils.h"
#include "SimpleIni.h"

AuthenticationDialog::AuthenticationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AuthenticationDialog)
{
    ui->setupUi(this);
    this->setResult(QDialog::Rejected);
    setInitialResult(initialForm());
    ui->lineEdit->setFocus(Qt::MouseFocusReason);
    ui->lineEdit->setSelection(0,0);
}

AuthenticationDialog::~AuthenticationDialog()
{
    delete ui;
}

int AuthenticationDialog::initialForm(const QString fileName)
{    
    CSimpleIniA ini;
    ini.LoadFile(fileName.toStdString().c_str());

    if(0 == ini.GetSection("OPERATORS")) {
        this->setResult(QDialog::Rejected);
        return 0;
    }

    QTextCodec *codec = QTextCodec::codecForName("Windows-1251");

    const char* use;
    use = ini.GetValue("OPERATORS", "Use");

    if(nullptr == use) {
        this->setResult(QDialog::Rejected);
        return 0;
    }
    if(0 == codec->toUnicode(use).toInt()){
        this->setResult(QDialog::Accepted);
        return 0;
    }

    const char* count;
    count = ini.GetValue("OPERATORS", "Count");

    if(nullptr == count) {
        this->setResult(QDialog::Rejected);
        return 0;
    }
    int userCount = codec->toUnicode(count).toInt();

    if(0 == userCount){
        this->setResult(QDialog::Accepted);
        return 0;
    }

    listUser.clear();
    for(int i = 0; i < userCount; i++) {
        QString group = "Operator_%1";
        group = group.arg(i);
        if(0 == ini.GetSection(group.toStdString().c_str())) {
            continue;
        }
        Operator newUser;
        newUser.setFN(codec->toUnicode(ini.GetValue(group.toStdString().c_str(), "FN")));
        newUser.setN1(codec->toUnicode(ini.GetValue(group.toStdString().c_str(), "N1")));
        newUser.setN2(codec->toUnicode(ini.GetValue(group.toStdString().c_str(), "N2")));
        newUser.setPW(QString(ini.GetValue(group.toStdString().c_str(), "PW")));

        const char * criptPasswordChar = ini.GetValue(group.toStdString().c_str(), "PW");
        QString criptPassword = QString::fromLatin1(criptPasswordChar);
        QString key = "start7";
        QString decriptPassword = Utils::xorCrypt(criptPassword, key);
        decriptPassword = codec->toUnicode(decriptPassword.toStdString().c_str());
        newUser.setDecriptPW(decriptPassword);

        listUser.append(newUser);
    }

    ui->comboBox->clear();
    for(int i = 0; i < listUser.size(); i++) {
        ui->comboBox->addItem(listUser.at(i).getOperatorLableText());
    }
    return 1;
}

void AuthenticationDialog::on_pushButton_clicked()
{
    QString dcrPWFromForm = ui->lineEdit->text();
    QString dcrPWFromUser = listUser.at(ui->comboBox->currentIndex()).getDecriptPW();

    if(dcrPWFromForm == dcrPWFromUser) {
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
