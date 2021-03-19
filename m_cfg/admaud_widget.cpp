#include "admaud_widget.h"
#include "ui_admaud_widget.h"
#include <QDebug>
#include <global.h>
#include <QStorageInfo>

#if (defined (_WIN32) || defined (_WIN64))
#include <Windows.h>
#endif

AdmAud_widget::AdmAud_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdmAud_widget)
{
    ui->setupUi(this);

    default_options();

    connect(&this->AdmKey,SIGNAL(usb_update()),this,SLOT(usb_update()));
}

AdmAud_widget::~AdmAud_widget()
{
    delete ui;
}

void AdmAud_widget::default_options()
{

    this->ui->comboBox->clear();
    this->ui->version->setText("");
    this->ui->DateTime->setText("");
    default_combobox();

}

void AdmAud_widget::default_combobox()
{
this->ui->comboBox->clear();
#if (defined (_WIN32) || defined (_WIN64))

qDebug()<<"[0]";
    LPWSTR lpbuffer;

    lpbuffer = new TCHAR[255];

qDebug()<<"[1]";
    for( int i = 0; i < 255; i++ ) lpbuffer[i] = 0;
    char dr[10];
   for( int i = 0; i < 10; i++ ) dr[i] = 0;
qDebug()<<"[2]";
    GetLogicalDriveStringsW(255,lpbuffer);

qDebug()<<"[3]";

    for( int i = 0; i < 255; i++ )
    {
     //   qDebug()<<"[4]";
       if( lpbuffer[i] == ':' )
       {
       dr[0] = lpbuffer[i-1];
       dr[1] = lpbuffer[i];
       dr[2] = lpbuffer[i+1];
  //     dr[3] = lpbuffer[i+2];


       QString str = dr;
       LPCWSTR path = (const wchar_t*) str.utf16();

       qDebug()<<"str: "<<str;

//GetDriveTypeW()
    if( GetDriveTypeW(path) == DRIVE_REMOVABLE )
    {
       qDebug()<<"[PROFIT] str: "<<str;
    this->ui->comboBox->addItem(str);
    }
       }
    }


#else
    qDebug()<<"[LINUX]";
    foreach (const QStorageInfo &storage, QStorageInfo::mountedVolumes()) {

    qDebug() << storage.rootPath();
    if (storage.isReadOnly())
   qDebug() << "isReadOnly:" << storage.isReadOnly();
    qDebug() << "name:" << storage.name();
    qDebug() << "fileSystemType:" << storage.fileSystemType();
    qDebug() << "size:" << storage.bytesTotal()/1000/1000 << "MB";
    qDebug() << "availableSize:" << storage.bytesAvailable()/1000/1000 << "MB";
    this->ui->comboBox->addItem(storage.rootPath());
    }

  /*  for (auto volume : QStorageInfo::mountedVolumes()) {
           qDebug() << "Name:" << volume.name();
           qDebug() << "Display name:" << volume.displayName();
           qDebug() << "Device:" << volume.device();
           qDebug() << "Root path:" << volume.rootPath();
           qDebug() << "File system type:" << volume.fileSystemType();
           qDebug() << "Is valid?" << (volume.isValid() ? "yes" : "no");
           qDebug() << "Is root?" << (volume.isRoot() ? "yes" : "no");
           qDebug() << "Is ready?" << (volume.isReady() ? "yes" : "no");
           qDebug() << "Is read only?" << (volume.isReadOnly() ? "yes" : "no");
           qDebug() << "Bytes available:" << volume.bytesAvailable();
           qDebug() << "Bytes free:" << volume.bytesFree();
           qDebug() << "Bytes total:" << volume.bytesTotal();

       }*/

#endif
}


/*
void MainWindowCFG::on_AdmAud_Create_pushButton_clicked()
{
    this->ui->AdmAud_version_lineEdit->setText("");
    this->ui->AdmAud_DateTime_lineEdit->setText("");

    QString filepath=this->ui->AdmAud_comboBox->currentText();

     filepath.append("auidit.adm");
    qDebug()<<filepath;
    AdmKey.create_key(filepath);


}
void MainWindowCFG::on_AdmAud_ChekIn_pushButton_clicked()
{
}
*/

void AdmAud_widget::on_Create_clicked()
{
    this->ui->version->setText("");
    this->ui->DateTime->setText("");

    QString filepath=this->ui->comboBox->currentText();

     filepath.append("auidit.adm");
    qDebug()<<filepath;
    AdmKey.create_key(filepath);
}

void AdmAud_widget::on_ChekIn_clicked()
{
    QString filepath=this->ui->comboBox->currentText();

     filepath.append("auidit.adm");
qDebug()<<filepath;
 AdmKey.check_key(filepath);

this->ui->version->setText(QString::number(AdmKey.getVersion()));
this->ui->DateTime->setText(AdmKey.getDatetime().toString());
this->ui->DateTime->setText(AdmKey.getDatetime().toString("dd.MM.yyyy hh:mm:ss"));

}

void AdmAud_widget::usb_update()
{
default_combobox();
}

void AdmAud_widget::on_comboBox_highlighted(int index)
{
  //  default_combobox();
}

void AdmAud_widget::on_pushButton_clicked()
{


#if (defined (_WIN32) || defined (_WIN64))

qDebug()<<"[0]";
    LPWSTR lpbuffer;

    lpbuffer = new TCHAR[255];

qDebug()<<"[1]";
    for( int i = 0; i < 255; i++ ) lpbuffer[i] = 0;
    char dr[10];
   for( int i = 0; i < 10; i++ ) dr[i] = 0;
qDebug()<<"[2]";
    GetLogicalDriveStringsW(255,lpbuffer);

qDebug()<<"[3]";

    for( int i = 0; i < 255; i++ )
    {
     //   qDebug()<<"[4]";
       if( lpbuffer[i] == ':' )
       {
       dr[0] = lpbuffer[i-1];
       dr[1] = lpbuffer[i];
       dr[2] = lpbuffer[i+1];
  //     dr[3] = lpbuffer[i+2];


       QString str = dr;
       LPCWSTR path = (const wchar_t*) str.utf16();

       qDebug()<<"str: "<<str;

//GetDriveTypeW()
    if( GetDriveTypeW(path) == DRIVE_REMOVABLE )
    {
       qDebug()<<"[PROFIT] str: "<<str;
    this->ui->comboBox->addItem(str);
    }
       }
    }


#else
    qDebug()<<"[LINUX]";
    foreach (const QStorageInfo &storage, QStorageInfo::mountedVolumes()) {

    qDebug() << storage.rootPath();
    if (storage.isReadOnly())
   qDebug() << "isReadOnly:" << storage.isReadOnly();
    qDebug() << "name:" << storage.name();
    qDebug() << "fileSystemType:" << storage.fileSystemType();
    qDebug() << "size:" << storage.bytesTotal()/1000/1000 << "MB";
    qDebug() << "availableSize:" << storage.bytesAvailable()/1000/1000 << "MB";

    }
#endif


}
