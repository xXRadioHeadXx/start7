#ifndef TABLEPRINT_H
#define TABLEPRINT_H

#include <QObject>
#include <QPrinter>
#include <QTableView>
#include <QTextDocument>

class TablePrint : public QObject
{
    Q_OBJECT
private:
    QTextDocument *document = nullptr;
public:
    explicit TablePrint(QObject *parent = nullptr);
    static bool prepareTmpFileHtmlTableFromModel(const QTableView * tableView);
    static bool print();
    bool printPreview();

private slots:
    void slotPreview(QPrinter *p);



signals:

};

#endif // TABLEPRINT_H
