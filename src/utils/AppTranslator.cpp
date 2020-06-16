#include <AppTranslator.h>

AppTranslator::AppTranslator(QApplication *app,
                             MainWindow *w,
                             QObject *parent) :
    QObject(parent),
    m_app(app),
    m_w(w)
{
    connect(m_w,
            SIGNAL(setTranslator(QTranslator*)),
            this,
            SLOT(installTranslator(QTranslator*)));

    connect(m_w,
            SIGNAL(resetTranslator(QTranslator*)),
            this,
            SLOT(removeTranslator(QTranslator*)));

    QTranslator *tr = m_w->getRuTranslator();
    qDebug() << "installTranslator" << m_app->installTranslator(tr);
}

AppTranslator::~AppTranslator()
{
    try
    {

    }
    catch(...)
    {
        qDebug() << "Assert(~AppTranslator)";
        return;
    }
}

void AppTranslator::installTranslator(QTranslator *tr)
{
    m_app->installTranslator(tr);
}

void AppTranslator::removeTranslator(QTranslator *tr)
{
    m_app->removeTranslator(tr);
}
