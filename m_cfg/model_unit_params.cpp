#include "model_unit_params.h"
#include <QColor>
#include <QDebug>

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

    case Qt::BackgroundRole:
         switch(index.column() % 3)
         {
         /*
         case 0:
         case 1:
         {
         Unit_Parametr* parameter=parametres.at(index.row());
         if(parameter->getNeeded())

         return QVariant(QColor(Qt::green));



         }
         break;
*/

         default://only to disable warning
             return QVariant(QColor(Qt::white));
         break;
         }
        break;

    }

    return QVariant();
}

bool Model_Unit_Params::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!index.isValid())
        return false;
    if (role == Qt::EditRole) {
        if (index.column() == 1)
        {
         Unit_Parametr* parameter=parametres.at(index.row());
               parameter->setValue(value.toString());

        }

        else if (index.column() == 2)
        {
            qDebug()<<"set needed: "<<value.toBool();
            Unit_Parametr*parameter=parametres.at(index.row());
                  parameter->setNeeded(value.toBool());
        }

        else
            return false;

    //    m_listMSG.replace(index.row(), item);


        emit dataChanged(index, index, QVector<int>() << Qt::DisplayRole << Qt::EditRole);
        return true;
    }
    return false;
}

QVariant Model_Unit_Params::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant();
}

Qt::ItemFlags Model_Unit_Params::flags(const QModelIndex &index) const
{
    Qt::ItemFlags result = Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    if(index.column()>0)
     result |= Qt::ItemIsEditable;
        return result;
}
