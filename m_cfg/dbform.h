#ifndef DBFORM_H
#define DBFORM_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class DBform;
}

class DBform : public QDialog
{
    Q_OBJECT

public:
    explicit DBform(QWidget *parent = nullptr);
    ~DBform();

    //при открытии формы нужно найти в QSqlDatabase db
    // и отобразить в таблице все бд с названием rif_bd0 (1,2,3)
    void find_rif_db(QSqlDatabase db);

    QList<QString> databases;

private slots:


    void on_add_DB_pushButton_clicked();

    void on_drop_BD_pushButton_clicked();

    void on_use_DB_pushButton_clicked();

private:
    Ui::DBform *ui;

signals:
    void create_db(QString db_name);
    void drop_db(QString db_name);
    void use_db(QString db_name);
};

#endif // DBFORM_H