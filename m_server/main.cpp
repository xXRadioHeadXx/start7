
#include "../src/utils/MessageBoxServer.h"
#include <QApplication>

#include "../src/utils/AppTranslator.h"
#include "MainWindowServer.h"
#include <QSplashScreen>
#include "../src/utils/RunGuard.h"

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);

    {
        RunGuard guardCopyServer( "start7_server" );
        if ( !guardCopyServer.tryToRun() ) {
            MessageBoxServer::infoTheProgramIsAlreadyRunning();
            guardCopyServer.release();
            return 0;
        }
    }

    {
        RunGuard guardCfg( "start7_cfg" );
        if ( !guardCfg.tryToRun() ) {
            MessageBoxServer::infoForTheProgramToWorkItIsNecessaryToTerminateTheModuleSettings();
            guardCfg.release();
            return 0;
        }
    }

    RunGuard guardServer( "start7_server" );
    guardServer.tryToRun();


    try
    {
        AuthenticationDialog ad;
        if(0 != ad.getInitialResult()) {
            if(QDialog::Accepted != ad.exec()) {
                MessageBoxServer::infoErrorInSelectingTheOperatorOfTheComplex();
                return 0;
            }
        }

        QSplashScreen splashScreen(/*const QPixmap& pixmap*/ QPixmap("://icons/logo.png"));

        splashScreen.show();
        splashScreen.showMessage(
            /*const QString &message*/ QObject::tr("Загрузка данных ..."),
            /*int alignment = Qt::AlignLeft*/ Qt::AlignHCenter | Qt::AlignBottom,
            /*const QColor &color = Qt::black*/ Qt::black);

        app.processEvents();

    //    app.setStyleSheet("QSplitter::handle { background-color: lightgray }");

        MainWindowServer w;
    //    AppTranslator tr(&app, &w);

        w.show();
    //    w.setRussian();

        splashScreen.finish(/*QWidget * mainWin*/ &w); //this если ваш класс наследуется от QWidget

        return app.exec();
    }
    catch (std::runtime_error &rte)
    {
        qFatal("catch runtime_error %s [main]", rte.what());
    }
    catch (std::exception &e)
    {
        qFatal("Error %s [main]", e.what());
    }
    catch (...)
    {
        qFatal("Error <unknown> [main]");
    }

}
