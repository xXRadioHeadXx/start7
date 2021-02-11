/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

//! [Quoting ModelView Tutorial]
// rif_widget_model.cpp
#include "rif_widget_model.h"
#include <QColor>


rif_widget_model::rif_widget_model(QObject *parent)
    : QAbstractTableModel(parent)
{
    for(int i(1), n(100); i < n; i++)
    {
        ComPort* port = new ComPort();
        comports.append(port);
    }
}

int rif_widget_model::rowCount(const QModelIndex & /*parent*/) const
{
   return 99;
}

int rif_widget_model::columnCount(const QModelIndex & /*parent*/) const
{
    return 3;
}

QVariant rif_widget_model::data(const QModelIndex &index, int role) const
{

    switch(role)
    {
   case Qt::DisplayRole:
    {
        switch(index.column())
        {
        case 0:
        {
        QString str("COM%1");
        str = str.arg(index.row()+1);
        return str;
        }
        break;

        case 1:
        {
        ComPort* port=comports.at(index.row());
        return port->get_RifPortSpeed();
        }
        break;

        case 2:
        {
            ComPort* port=comports.at(index.row());
            return port->get_RifPortInterval();
        }
        break;
        }


    }
    break;

    case Qt::BackgroundRole:
         switch(index.column() % 3)
         {

         case 1:
         {
         ComPort* port=comports.at(index.row());
         if(port->get_RifPortSpeed()!=4800)

         return QVariant(QColor(Qt::green));


         }
         break;

         case 2:
         {
             ComPort* port=comports.at(index.row());
             if(port->get_RifPortInterval()!=50)

             return QVariant(QColor(Qt::green));
         }
         break;

         default://only to disable warning
             return QVariant(QColor(Qt::white));
         break;
         }

    break;



    }

    return QVariant();

}

bool rif_widget_model::setData(const QModelIndex &index, const QVariant &value, int role)
{

    if(!index.isValid())
        return false;
    if (role == Qt::EditRole) {
        if (index.column() == 1)
        {
         ComPort* port=comports.at(index.row());
               port->set_RifPortSpeed(value.toInt());

        }

        else if (index.column() == 2)
        {
            ComPort* port=comports.at(index.row());
                  port->set_RifPortInterval(value.toInt());

        }

        else
            return false;

    //    m_listMSG.replace(index.row(), item);


        emit dataChanged(index, index, QVector<int>() << Qt::DisplayRole << Qt::EditRole);
        return true;
    }
    return false;
}



Qt::ItemFlags rif_widget_model::flags(const QModelIndex &index) const
{
    Qt::ItemFlags result = Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    if(index.column()>0)
     result |= Qt::ItemIsEditable;
        return result;
}
//! [Quoting ModelView Tutorial]
