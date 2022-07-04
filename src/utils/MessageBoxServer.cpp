#include "../src/utils/MessageBoxServer.h"

#include "../src/entity/JourEntity.h"
#include <QMessageBox>

int MessageBoxServer::infoAllRequiredFieldsInTheDatabaseAreNotFilledIn()
{
    return QMessageBox::warning(nullptr,
                                MessageBoxServer::instance().titleError,
                                MessageBoxServer::instance().iAllRequiredFieldsInTheDatabaseAreNotFilledIn);;
}

int MessageBoxServer::questionDoYouReallyWantToDisconnectTheDevice()
{
    return QMessageBox::question(nullptr,
                                 MessageBoxServer::instance().titleWarning,
                                 MessageBoxServer::instance().qDoYouReallyWantToDisconnectTheDevice,
                                 QMessageBox::Ok | QMessageBox::Cancel,
                                 QMessageBox::Ok);
}

int MessageBoxServer::questionRemoveTheControl()
{
    return QMessageBox::question(nullptr,
                                 MessageBoxServer::instance().titleWarning,
                                 MessageBoxServer::instance().qRemoveTheControl,
                                 QMessageBox::Ok | QMessageBox::Cancel,
                                 QMessageBox::Ok);;
}

int MessageBoxServer::questionRestoreControl()
{
    return QMessageBox::question(nullptr,
                                 MessageBoxServer::instance().titleWarning,
                                 MessageBoxServer::instance().qRestoreControl,
                                 QMessageBox::Ok | QMessageBox::Cancel,
                                 QMessageBox::Ok);;
}

int MessageBoxServer::questionShutDownAndExitTheProgram()
{
    return QMessageBox::warning(nullptr,
                                MessageBoxServer::instance().titleWarning,
                                MessageBoxServer::instance().qShutDownAndExitTheProgram,
                                QMessageBox::Ok | QMessageBox::Cancel,
                                QMessageBox::Ok);;
}

int MessageBoxServer::questionStartANewShift()
{
    return QMessageBox::question(nullptr,
                                 MessageBoxServer::instance().titleWarning,
                                 MessageBoxServer::instance().qStartANewShift,
                                 QMessageBox::Ok | QMessageBox::Cancel,
                                 QMessageBox::Ok);
}

int MessageBoxServer::infoErrorInSelectingTheOperatorOfTheComplex()
{
    return QMessageBox::warning(nullptr,
                                MessageBoxServer::instance().titleWarning,
                                MessageBoxServer::instance().iErrorInSelectingTheOperatorOfTheComplex);
}

int MessageBoxServer::infoTheProgramIsAlreadyRunning()
{
    return QMessageBox::critical(nullptr,
                                 MessageBoxServer::instance().titleWarning,
                                 MessageBoxServer::instance().iTheProgramIsAlreadyRunning);
}

int MessageBoxServer::infoForTheProgramToWorkItIsNecessaryToTerminateTheModuleSettings()
{
    return QMessageBox::critical(nullptr,
                                 MessageBoxServer::instance().titleWarning,
                                 MessageBoxServer::instance().iForTheProgramToWorkItIsNecessaryToTerminateTheModuleSettings);

}

int MessageBoxServer::infoSensorParametersRecordedSuccessfully()
{
    return QMessageBox::information(nullptr,
                                    MessageBoxServer::instance().titleInfo,
                                    MessageBoxServer::instance().iSensorParametersRecordedSuccessfully,
                                    QMessageBox::Ok);
}

int MessageBoxServer::infoErrorRecordingSensorParameters()
{
    return QMessageBox::warning(nullptr,
                                MessageBoxServer::instance().titleError,
                                MessageBoxServer::instance().iErrorRecordingSensorParameters,
                                QMessageBox::Ok);
}

int MessageBoxServer::infoTheOperationCannotBePerformedThereIsNoConnectionWithTheSensor(const QString &nameUN)
{
    auto tmpStr = MessageBoxServer::instance().iTheOperationCannotBePerformedThereIsNoConnectionWithTheSensor;
    tmpStr = tmpStr.arg((!nameUN.isEmpty() ? " " : "") + nameUN);
    return QMessageBox::warning(nullptr,
                                MessageBoxServer::instance().titleError,
                                tmpStr, //MessageBoxServer::instance().iTheOperationCannotBePerformedThereIsNoConnectionWithTheSensor,
                                QMessageBox::Ok);
}

int MessageBoxServer::infoErrorExecutingTheLockOpeningCommand()
{
    return QMessageBox::warning(nullptr,
                                MessageBoxServer::instance().titleError,
                                MessageBoxServer::instance().iErrorExecutingTheLockOpeningCommand,
                                QMessageBox::Ok);
}

int MessageBoxServer::infoErrorExecutingTheOnAutoCommand()
{
    return QMessageBox::warning(nullptr,
                                MessageBoxServer::instance().titleError,
                                MessageBoxServer::instance().iErrorExecutingTheOnAutoCommand,
                                QMessageBox::Ok);
}

int MessageBoxServer::infoErrorExecutingTheOffAutoCommand()
{
    return QMessageBox::warning(nullptr,
                                MessageBoxServer::instance().titleError,
                                MessageBoxServer::instance().iErrorExecutingTheOffAutoCommand,
                                QMessageBox::Ok);
}

int MessageBoxServer::infoErrorExecutingTheDKCommand()
{
    return QMessageBox::warning(nullptr,
                                MessageBoxServer::instance().titleError,
                                MessageBoxServer::instance().iErrorExecutingTheDKCommand,
                                QMessageBox::Ok);
}

void MessageBoxServer::showAttentionJourMsg(const JourEntity &jour)
{
//    QString message = "<h2>Имя</h2><h2 style="color: #2e6c80;">Сообщение</h2>";
    QString message = "<h4>%1</h4><h4 style=\"color: %2;\">%3</h4>";
    message = message.arg(jour.getObject(), jour.getColor().name(QColor::HexRgb), jour.getComment());

    QMessageBox * msgBox = new QMessageBox(QMessageBox::Warning,
                                           MessageBoxServer::instance().titleAttention,
                                           message,
                                           QMessageBox::NoButton,
                                           nullptr,
                                           Qt::ForeignWindow);
    msgBox->setWindowModality(Qt::NonModal);

    msgBox->connect(msgBox, &QDialog::finished, msgBox, &QMessageBox::deleteLater);


    msgBox->move(400,250);

    msgBox->show();
    return;
}

int MessageBoxServer::questionInsertAdminKeyAndClickOK()
{
    return QMessageBox::question(nullptr,
                                 MessageBoxServer::instance().titleWarning,
                                 MessageBoxServer::instance().qInsertAdminKeyAndClickOK,
                                 QMessageBox::Ok | QMessageBox::Cancel,
                                 QMessageBox::Ok);
}

void MessageBoxServer::infoAdminKeyNotFound()
{
    QMessageBox * msgBox = new QMessageBox(QMessageBox::Warning,
                                           MessageBoxServer::instance().titleAttention,
                                           MessageBoxServer::instance().iAdminKeyNotFound,
                                           QMessageBox::NoButton,
                                           nullptr,
                                           Qt::ForeignWindow);
    msgBox->setWindowModality(Qt::NonModal);

    msgBox->connect(msgBox, &QDialog::finished, msgBox, &QMessageBox::deleteLater);

    msgBox->show();
    return;
}
