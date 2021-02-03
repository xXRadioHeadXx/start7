#include "admkeygenerator.h"
#include <QFile>
#include <QDataStream>
#include <QDebug>
#include <QtCore/QtEndian>
#include <QDateTime>


AdmKeyGenerator::AdmKeyGenerator()
{

}


double AdmKeyGenerator::getVersion() const
{
    return version;
}

QDateTime AdmKeyGenerator::getDatetime() const
{
    return datetime;
}

void AdmKeyGenerator::create_key(QString filepath)
{
    QFile file(filepath);

    if(file.open(QIODevice::WriteOnly))
    {
        QDataStream in1(&file);    // read the data serialized from the file

        double a;
        double b;
        double c;

        b=2;

       double dt=QDateTime::currentDateTime().toTime_t();
    //    double a1 =static_cast<double>(dt)/static_cast<double>(86400);
        double a1 =static_cast<double>( static_cast<double>(dt)/static_cast<double>(86400.000));

        qDebug()<<"dt "<<QString::number(dt, 'f', 5);


        qDebug()<<"a1 "<<QString::number(a1, 'f', 5);

        a=(a1)+25569.16666-0.04166;


        c=b+a;

        a=qFromBigEndian<quint64 >(a);
        b=qFromBigEndian<quint64 >(b);
        c=qFromBigEndian<quint64 >(c);



        in1  << b << a << c;

        file.close();

        dialog.showMessage("ФАЙЛ АУДИТА СОЗДАН");
        dialog.exec();


    }
    else
    {
        dialog.showMessage("Диск не найден!");
        dialog.exec();

         qDebug()<<"[FALSE]";

    }



}

bool AdmKeyGenerator::check_key(QString filepath)
{
    QFile file(filepath);


    if(file.open(QIODevice::ReadOnly))
    {
        QDataStream in1(&file);    // read the data serialized from the file
        double a;
        double b;
        double c;

        in1  >> b >> a >> c;

    //    b =qToLittleEndian(b);

        qDebug()<<"int a "<<a;

        qDebug()<<"double b "<<b;
        //поменяй байты местами.

        file.close();

        b=qFromBigEndian<quint64 >(b);

        qDebug()<<"qFromBigEndian "  <<b;
        version=b;
        //          this->ui->lineEdit->setText(QString::number(b));



    qDebug()<<"a "<<a
           <<"<qFromBigEndian<quint64 >(a) "<<qFromBigEndian<quint64 >(a)
           <<"qFromLittleEndian<quint64 >(a) "<<qFromLittleEndian<quint64 >(a)
           <<"qToBigEndian<quint64 >(a) "<<qToBigEndian<quint64 >(a)
           <<"qToLittleEndian<quint64 >(a) "<<qToLittleEndian<quint64 >(a);





        a=qFromBigEndian<quint64 >(a);

        qDebug()<<"qFromBigEndian "  <<a;



     //   int time_t = (int)((a-25569.16666) * 86400);
         int time_t = (int)((a-25569.16666+0.04166) * 86400);
         qDebug()<<"time_t "<<time_t;
         QDateTime dt = QDateTime::fromTime_t( time_t );

        qDebug()<<dt;
        datetime=dt;
    //    this->ui->lineEdit_2->setText(dt.toString());

        c=qFromBigEndian<quint64 >(c);

        qDebug()<<"a "<<a;
        qDebug()<<"b "<<b;
        qDebug()<<"c "<<c;

        if(c==a+b)
            qDebug()<<"[PROFIT]";
        else
            {
            dialog.showMessage("Ошибка контрольной суммы!");
            dialog.exec();
            return false;
             qDebug()<<"[FALSE]";
            }

    }
    else
    {
        dialog.showMessage("Диск не найден!");
        dialog.exec();
        return false;
         qDebug()<<"[FALSE]";

    }
return true;

}
