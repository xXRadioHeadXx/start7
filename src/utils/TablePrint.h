#ifndef TABLEPRINT_H
#define TABLEPRINT_H

#include <QObject>
#include <QTableView>

class TablePrint : public QObject
{
    Q_OBJECT
public:
    explicit TablePrint(QObject *parent = nullptr);
    static bool prepareTmpFileHtmlTableFromModel(const QTableView * tableView);
    static bool print();
    static bool printPreview();



signals:

};

#endif // TABLEPRINT_H
