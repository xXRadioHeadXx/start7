#ifndef UNITFINDER_H
#define UNITFINDER_H

#include <QWidget>
#include "model_unit_params.h"
#include <unit_finder_delegate.h>
#include "rif_widget_delegate.h"

namespace Ui {
class UnitFinder;
}

class UnitFinder : public QWidget
{
    Q_OBJECT

public:
    explicit UnitFinder(QWidget *parent = nullptr);
    ~UnitFinder();

    QString get_value(QString Name);

private:
    unit_finder_delegate* delegate;
    rif_widget_delegate* delegate_1;
    Model_Unit_Params* model;
    Ui::UnitFinder *ui;

    QMap<QString,QString> result;



signals:
    void options_to_find(QList<QString>);
    void prev();
    void next();
    void clear_list_equals();
private slots:
    void on_pushButton_clicked();

    void on_prev_button_clicked();
    void on_next_button_clicked();
    void on_pushButton_4_clicked();
};

#endif // UNITFINDER_H
