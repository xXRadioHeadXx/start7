#include "my_combobox.h"
#include <QDebug>
//#include <global.hpp>
#include <QStorageInfo>

#if (defined (_WIN32) || defined (_WIN64))
#include <Windows.h>
#endif
My_combobox::My_combobox(QWidget *parent)
    : QComboBox(parent)
{
//for(int i=0;i<10;i++)
//    this->addItem(QString::number(i));

}

void My_combobox::showPopup()
{
    qDebug()<<"popUp";


    this->clear();
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
        this->addItem(str);
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
        this->addItem(storage.rootPath());
        //this->ui->comboBox->addItem(storage.rootPath());
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

    QComboBox::showPopup();
}
