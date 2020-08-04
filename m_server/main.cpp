
#include <QApplication>

#include <AppTranslator.h>
#include <MainWindowServer.h>
#include <AuthenticationDialog.h>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    AuthenticationDialog ad;
    Operator op;
    if(QDialog::Accepted == ad.exec()) {
       op = ad.getApprovedOperator();
    } else {
        QMessageBox::warning(nullptr, QObject::trUtf8("Ошибка"),
                             QObject::trUtf8("Ошибка выбора оператора комплекса!"));
        return 0;
    }

    MainWindowServer w;
    w.setApprovedOperator(op);
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
