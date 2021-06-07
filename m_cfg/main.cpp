#include "MainWindowCFG.h"
#include <QDebug>
#include "Icons.h"
#include <QIcon>
#include <QMutex>
#include <QSystemSemaphore>
#include "first_dialog.h"

#if (defined (_WIN32) || defined (_WIN64))
#include <Windows.h>
#endif

#include <QApplication>
#include <RunGuard.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    {
        RunGuard guardCopyCfg( "start7_cfg" );
        if ( !guardCopyCfg.tryToRun() ) {
            QMessageBox::critical(nullptr,
                                  QObject::tr("Предупреждение"),
                                  QObject::tr("Программа уже запущена!"));
            guardCopyCfg.release();
            return 0;
        }
    }

    {
        RunGuard guardServer( "start7_server" );
        if ( !guardServer.tryToRun() ) {
            QMessageBox::critical(nullptr,
                                  QObject::tr("Предупреждение"),
                                  QObject::tr("Для работы программа необходимо завершить работу модуля \"Сервер\"!"));
            guardServer.release();
            return 0;
        }
    }

    RunGuard guardCopyCfg( "start7_cfg" );
    guardCopyCfg.tryToRun();


//First change

#if (defined (_WIN32) || defined (_WIN64))
    {
    HANDLE hMutex_Mcfg =  CreateMutexA(NULL, false, "RIFx_Mcfg_by_Start7");
     if (GetLastError() == ERROR_ALREADY_EXISTS)
        {
           CloseHandle(hMutex_Mcfg);
           QMessageBox::critical(0,"Ошибка","Утилита уже запущена");

           return FALSE;
        }
    HANDLE hMutex_Mserver =  CreateMutexA(NULL, false, "RIFx_Mserver_by_Start7");
     if (GetLastError() == ERROR_ALREADY_EXISTS)
        {
           CloseHandle(hMutex_Mserver);
           QMessageBox::critical(0,"Ошибка","Для работы программы необходимо завершить работу модуля \"Сервер\"!");

           return FALSE;
        }
    CloseHandle(hMutex_Mserver);

    HANDLE hMutex_Mclient =  CreateMutexA(NULL, false, "RIFx_Mserver_by_Start7");
     if (GetLastError() == ERROR_ALREADY_EXISTS)
        {
           CloseHandle(hMutex_Mclient);
           QMessageBox::critical(0,"Ошибка","Для работы программы необходимо завершить работу модуля \"Клиент\"!");

           return FALSE;
        }
    CloseHandle(hMutex_Mclient);

}
#endif

    MainWindowCFG w;
    w.setWindowIcon(QIcon::fromTheme(":icons/exec.ico"));
    w.show();





    return a.exec();
}
