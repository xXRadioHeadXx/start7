#ifndef TABLEPRINT_H
#define TABLEPRINT_H

#include <QObject>
#include <QTableView>

class TablePrint : public QObject
{
    Q_OBJECT
public:
    explicit TablePrint(QObject *parent = nullptr);
    static bool createHtmlTableFromModel(const QTableView * tableView);
    static void print();


signals:

};

#endif // TABLEPRINT_H
