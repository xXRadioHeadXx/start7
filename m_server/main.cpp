
#include <QApplication>

#include <AppTranslator.h>
#include <MainWindowServer.h>
//#include <AuthenticationDialog.h>
#include <QMessageBox>
#include <QSplashScreen>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    AuthenticationDialog ad;
    if(0 != ad.getInitialResult()) {
        if(QDialog::Accepted != ad.exec()) {
            QMessageBox::warning(nullptr, QObject::trUtf8("Ошибка"),
                                 QObject::trUtf8("Ошибка выбора оператора комплекса!"));
            return 0;
        }
    }

    QSplashScreen splashScreen(/*const QPixmap& pixmap*/ QPixmap("://icons/logo.png"));

    splashScreen.showMessage(
        /*const QString &message*/ QObject::trUtf8("Загрузка данных ..."),
        /*int alignment = Qt::AlignLeft*/ Qt::AlignHCenter | Qt::AlignBottom,
        /*const QColor &color = Qt::black*/ Qt::black);

    MainWindowServer w;
//    AppTranslator tr(&app, &w);

    w.show();
//    w.setRussian();

//    splashScreen.finish(/*QWidget * mainWin*/ &w); //this если ваш класс наследуется от QWidget

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
