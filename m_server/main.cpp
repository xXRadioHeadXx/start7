
#include <QApplication>

#include <AppTranslator.h>
#include <MainWindowServer.h>
#include <QMessageBox>
#include <QSplashScreen>
#include <RunGuard.h>

int main(int argc, char *argv[])
{

    RunGuard guardCopyServer( "start7_server" );
    if ( !guardCopyServer.tryToRun() )
        return 0;

    RunGuard guardCfg( "start7_cfg" );
    if ( !guardCfg.tryToRun() )
        return 0;


    QApplication app(argc, argv);

    AuthenticationDialog ad;
    if(0 != ad.getInitialResult()) {
        if(QDialog::Accepted != ad.exec()) {
            QMessageBox::warning(nullptr, QObject::tr("Ошибка"),
                                 QObject::tr("Ошибка выбора оператора комплекса!"));
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

    MainWindowServer w;
//    AppTranslator tr(&app, &w);

    w.show();
//    w.setRussian();

    splashScreen.finish(/*QWidget * mainWin*/ &w); //this если ваш класс наследуется от QWidget

    try
    {
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
