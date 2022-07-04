#ifndef MESSAGEBOXSERVER_H
#define MESSAGEBOXSERVER_H

#include "../template/SingletonTemplate.h"

#include <QObject>
#include <QString>
#include <QMessageBox>

class JourEntity;
class MessageBoxServer : public SingletonTemplate<MessageBoxServer>
{
    const QString titleError = QObject::tr("Ошибка");
    const QString titleWarning = QObject::tr("Предупреждение");
    const QString titleInfo = QObject::tr("Инфо");
    const QString titleAttention = QObject::tr("Внимание");

    const QString iAllRequiredFieldsInTheDatabaseAreNotFilledIn = QObject::tr("Не заполнены все обязательные поля в базе данных!");
    const QString qDoYouReallyWantToDisconnectTheDevice = QObject::tr("Вы действительно хотите отключить устройство?");
    const QString qRemoveTheControl = QObject::tr("Убрать контроль?");
    const QString qRestoreControl = QObject::tr("Восстановить контроль?");
    const QString qShutDownAndExitTheProgram = QObject::tr("Завершить работу и выйти из программы?");
    const QString qStartANewShift = QObject::tr("Начать новую смену?");
    const QString iErrorInSelectingTheOperatorOfTheComplex = QObject::tr("Ошибка выбора оператора комплекса!");
    const QString iTheProgramIsAlreadyRunning = QObject::tr("Программа уже запущена!");
    const QString iForTheProgramToWorkItIsNecessaryToTerminateTheModuleSettings = QObject::tr("Для работы программа необходимо завершить работу модуля \"Настройки\"!");
    const QString iSensorParametersRecordedSuccessfully = QObject::tr("Параметры датчика записаны успешно!");
    const QString iErrorRecordingSensorParameters = QObject::tr("Ошибка записи параметров датчика!");
    const QString iTheOperationCannotBePerformedThereIsNoConnectionWithTheSensor = QObject::tr("Нельзя выполнить операцию. Отсутствует связь с устройством%1!");
    const QString iErrorExecutingTheLockOpeningCommand = QObject::tr("Ошибка выполнения команды открытия замка!");
    const QString iErrorExecutingTheOnAutoCommand = QObject::tr("Ошибка выполнения команды Вкл (Авто)!");
    const QString iErrorExecutingTheOffAutoCommand = QObject::tr("Ошибка выполнения команды Выкл (Авто)!");
    const QString iErrorExecutingTheDKCommand = QObject::tr("Ошибка выполнения команды ДК!");
    const QString qInsertAdminKeyAndClickOK = QObject::tr("Вставте ключ администратора и нажмите OK.");
    const QString iAdminKeyNotFound = QObject::tr("Ключ администратора не найден!");


public:

    static int infoAllRequiredFieldsInTheDatabaseAreNotFilledIn();
    static int questionDoYouReallyWantToDisconnectTheDevice();
    static int questionRemoveTheControl();
    static int questionRestoreControl();
    static int questionShutDownAndExitTheProgram();
    static int questionStartANewShift();
    static int infoErrorInSelectingTheOperatorOfTheComplex();
    static int infoTheProgramIsAlreadyRunning();
    static int infoForTheProgramToWorkItIsNecessaryToTerminateTheModuleSettings();
    static int infoSensorParametersRecordedSuccessfully();
    static int infoErrorRecordingSensorParameters();
    static int infoTheOperationCannotBePerformedThereIsNoConnectionWithTheSensor(const QString &nameUN = "");
    static int infoErrorExecutingTheLockOpeningCommand();
    static int infoErrorExecutingTheOnAutoCommand();
    static int infoErrorExecutingTheOffAutoCommand();
    static int infoErrorExecutingTheDKCommand();
    static void showAttentionJourMsg(const JourEntity & jour);
    static int questionInsertAdminKeyAndClickOK();
    static void infoAdminKeyNotFound();


};

#endif // MESSAGEBOXSERVER_H
