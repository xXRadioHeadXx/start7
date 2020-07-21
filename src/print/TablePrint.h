#ifndef TABLEPRINT_H
#define TABLEPRINT_H

#include <QObject>
#include <QPrinter>
#include <QTableView>
#include <QTextDocument>
//#include <QWebView>

class TablePrint : public QObject
{
    Q_OBJECT
private:
    QTextDocument * document = nullptr;
//    QWebView *printHtmlView = nullptr;
public:
    explicit TablePrint(QObject *parent = nullptr);
    static bool prepareTmpFileHtmlTableFromModel(const QTableView * tableView);
    static bool print();
    static bool printPdf();
    bool printPreview();

private slots:
    void slotPreview(QPrinter *p);
//    void htmlRender();


signals:

};

#endif // TABLEPRINT_H
