#include "UnitNodeTreeItem.h"

#include <QVariant>
#include "../src/utils/ServerSettingUtils.h"
#include <QSharedPointer>

int UnitNodeTreeItem::treeColumnCount() const
{
    return 1;
}

QVariant UnitNodeTreeItem::data(int column) const
{
    Q_UNUSED(column)
    return QVariant();
}
