#ifndef MODEL_UNIT_PARAMS_H
#define MODEL_UNIT_PARAMS_H

#include <QObject>
#include <QAbstractTableModel>
#include "unit_parametr.h"

class Model_Unit_Params : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit Model_Unit_Params(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    virtual  bool  setData(const QModelIndex &index, const QVariant &value, int role);
    // РѕС‚РѕР±СЂР°Р¶РµРЅРёРµ   РЅР°Р·РІР°РЅРёР№   СЃС‚РѕР»Р±С†РѕРІ
    virtual QVariant headerData( int section, Qt::Orientation orientation, int role) const;
    // РІРѕР·РјРѕР¶РЅРѕСЃС‚СЊ СЂРµРґР°РєС‚РёСЂРѕРІР°РЅРёСЏ СЌР»РµРјРµРЅС‚Р°
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;



    inline QModelIndex index(int row, int column, const QModelIndex &parent) const {
        if(hasIndex(row, column, parent))
            return createIndex(row, column);
        else
            return QModelIndex();
    }


    inline QModelIndex parent(const QModelIndex &) const { return QModelIndex(); }

private:

    QList<Unit_Parametr*> parametres;

    QList<QString> l_params={
        "Type",
        "Num1",
        "Num2",
        "Num3",

        "DK",
        "Bazalt",
        "Metka",
        "Razriv",
        "AdamOff",
        "AlarmMsgOn",
        "ConnectBlock",
        "OutType",




        "UdpUse",
        "UdpAdress",
        "UdpPort",
        "UdpTimeout",




        "Icon1Path",
        "Icon2Path",
        "Icon3Path",
        "Icon4Path"
    };


};

#endif // MODEL_UNIT_PARAMS_H
