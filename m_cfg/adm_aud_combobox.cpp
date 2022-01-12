#include "adm_aud_combobox.h"
#include <QDebug>
//#include <global.h>
#include <QStorageInfo>
#include <QProcess>

#if (defined (_WIN32) || defined (_WIN64))
#include <Windows.h>
#endif
adm_aud_combobox::adm_aud_combobox(QWidget *parent)
    : QComboBox(parent)
{
//for(int i=0;i<10;i++)
//    this->addItem(QString::number(i));

}

void adm_aud_combobox::showPopup()
{
    //qDebug()<<"popUp";


    this->clear();
    #if (defined (_WIN32) || defined (_WIN64))

    //qDebug()<<"[0]";
        LPWSTR lpbuffer;

        lpbuffer = new TCHAR[255];

    //qDebug()<<"[1]";
        for( int i = 0; i < 255; i++ ) lpbuffer[i] = 0;
        char dr[10];
       for( int i = 0; i < 10; i++ ) dr[i] = 0;
    //qDebug()<<"[2]";
        GetLogicalDriveStringsW(255,lpbuffer);

    //qDebug()<<"[3]";

        for( int i = 0; i < 255; i++ )
        {
         //   //qDebug()<<"[4]";
           if( lpbuffer[i] == ':' )
           {
           dr[0] = lpbuffer[i-1];
           dr[1] = lpbuffer[i];
           dr[2] = lpbuffer[i+1];
      //     dr[3] = lpbuffer[i+2];


           QString str = dr;
           LPCWSTR path = (const wchar_t*) str.utf16();

           //qDebug()<<"str: "<<str;

    //GetDriveTypeW()
        if( GetDriveTypeW(path) == DRIVE_REMOVABLE )
        {
           //qDebug()<<"[PROFIT] str: "<<str;
        this->addItem(str);
        }
           }
        }


    #else
    qDebug()<<"[LINUX]";

        QProcess process;
        QString LProc("devs=`ls -al /dev/disk/by-path/*usb*part* 2>/dev/null | awk '{print($11)}'`; for dev in $devs; do dev=${dev##*\/};  echo -n $(mount |  grep \`echo -n ${dev}\` | awk '{print($3)}');echo -n \" \"; done");
        process.start("sh", QStringList() << "-c" << LProc);
        process.waitForFinished(-1); // will wait forever until finished
        QString stdout = process.readAllStandardOutput();
        QString stderr = process.readAllStandardError();
        QStringList query = stdout.split(" ");
        for (int i = 0; i < query.size()-1; ++i)      {
             qDebug() << query.at(i);
             QString str="";
             str+=query.at(i);
             str+="/";
             this->addItem(str);
        }

      /*  for (auto volume : QStorageInfo::mountedVolumes()) {
               //qDebug() << "Name:" << volume.name();
               //qDebug() << "Display name:" << volume.displayName();
               //qDebug() << "Device:" << volume.device();
               //qDebug() << "Root path:" << volume.rootPath();
               //qDebug() << "File system type:" << volume.fileSystemType();
               //qDebug() << "Is valid?" << (volume.isValid() ? "yes" : "no");
               //qDebug() << "Is root?" << (volume.isRoot() ? "yes" : "no");
               //qDebug() << "Is ready?" << (volume.isReady() ? "yes" : "no");
               //qDebug() << "Is read only?" << (volume.isReadOnly() ? "yes" : "no");
               //qDebug() << "Bytes available:" << volume.bytesAvailable();
               //qDebug() << "Bytes free:" << volume.bytesFree();
               //qDebug() << "Bytes total:" << volume.bytesTotal();

           }*/

    #endif

    QComboBox::showPopup();
}
