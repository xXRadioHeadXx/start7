#include "MainWindowCFG.h"
#include <QDebug>
#include "Icons.h"
#include <QIcon>
#include <QMutex>
#include <QSystemSemaphore>

#if (defined (_WIN32) || defined (_WIN64))
#include <Windows.h>
#endif

#include <QApplication>
#include <RunGuard.h>

int main(int argc, char *argv[])
{
    RunGuard guardCopyCfg( "start7_cfg" );
    if ( !guardCopyCfg.tryToRun() )
        return 0;

    RunGuard guardServer( "start7_server" );
    if ( !guardServer.tryToRun() )
        return 0;


    QApplication a(argc, argv);

//First change

/*
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
*/

    MainWindowCFG w;
    w.setWindowIcon(QIcon::fromTheme(":icons/exec.ico"));
    w.show();



    return a.exec();
}
