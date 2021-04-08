
#include <QApplication>

#include <AppTranslator.h>
#include <MainWindowServer.h>
#include <QMessageBox>
#include <QSplashScreen>
#include <RunGuard.h>

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);

    RunGuard guardCopyServer( "start7_server" );
    if ( !guardCopyServer.tryToRun() ) {
        QMessageBox::critical(nullptr,
                              QObject::tr("Предупреждение"),
                              QObject::tr("Программа уже запущена!"));
        return 0;
    }

    RunGuard guardCfg( "start7_cfg" );
    if ( !guardCfg.tryToRun() ) {
        QMessageBox::critical(nullptr,
                             QObject::tr("Предупреждение"),
                             QObject::tr("Для работы программа необходимо завершить работу модуля \"Сервер\"!"));
        return 0;
    }

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
