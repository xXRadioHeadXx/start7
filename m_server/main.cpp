
#include <QApplication>

#include <AppTranslator.h>
#include <MainWindowServer.h>
//#include <AuthenticationDialog.h>
#include <QMessageBox>

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

    MainWindowServer w;
//    AppTranslator tr(&app, &w);

    w.show();
//    w.setRussian();

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
