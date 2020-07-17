
#include <QApplication>

#include <AppTranslator.h>
#include <MainWindowServer.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
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
