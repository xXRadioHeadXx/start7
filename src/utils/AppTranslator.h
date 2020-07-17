#ifndef APPTRANSLATOR_H
#define APPTRANSLATOR_H

#include <QObject>
#include <QApplication>
#include <MainWindowServer.h>
class AppTranslator : public QObject
{
    Q_OBJECT
public:
    QApplication *m_app;
    MainWindowServer *m_w;
    explicit AppTranslator(QApplication *app,
                           MainWindowServer *w,
                           QObject *parent = nullptr);
    virtual ~AppTranslator();

signals:

public slots:
    void installTranslator(QTranslator *tr);
    void removeTranslator(QTranslator *tr);
};

#endif // APPTRANSLATOR_H
