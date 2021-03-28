#ifndef TABLEPRINT_H
#define TABLEPRINT_H

#include <QObject>

class QTableView;
class QPrinter;
class QTextDocument;
class TablePrint : public QObject
{
    Q_OBJECT
private:
    QTextDocument * document = nullptr;
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
