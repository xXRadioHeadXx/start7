#ifndef UNITFINDER_H
#define UNITFINDER_H

#include <QWidget>

namespace Ui {
class UnitFinder;
}

class UnitFinder : public QWidget
{
    Q_OBJECT

public:
    explicit UnitFinder(QWidget *parent = nullptr);
    ~UnitFinder();

private:
    Ui::UnitFinder *ui;
};

#endif // UNITFINDER_H
