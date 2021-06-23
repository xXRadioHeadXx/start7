#include "model_unit_params.h"

Model_Unit_Params::Model_Unit_Params(QObject *parent) : QAbstractTableModel(parent)
{
    for(int i(0), n(this->l_params.count()); i < n; i++)
    {
      Unit_Parametr* parametr=new Unit_Parametr(this->l_params.at(i));
    parametres.append(parametr);

    }
}

int Model_Unit_Params::rowCount(const QModelIndex &parent) const
{
    return l_params.count();
}

int Model_Unit_Params::columnCount(const QModelIndex &parent) const
{
    return 3;
}

QVariant Model_Unit_Params::data(const QModelIndex &index, int role) const
{

    switch(role)
    {
   case Qt::DisplayRole:
    {
        switch(index.column())
        {
        case 0:
        {

        return parametres.at(index.row())->getName();
        }
        break;

        case 1:
        {

        return parametres.at(index.row())->getValue();
        }
        break;

        case 2:
        {

        return parametres.at(index.row())->getNeeded();
        }
        break;
        }


    }
    break;


    }

return QVariant();
}
