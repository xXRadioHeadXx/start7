#include "my_combobox.h"
#include <QDebug>
#include <QMenu>
#include <QContextMenuEvent>
#include <QLineEdit>

#if (defined (_WIN32) || defined (_WIN64))
#include <Windows.h>
#endif
my_combobox::my_combobox(QWidget *parent)
    : QComboBox(parent)
{

//  QRegExpValidator*  validator = new QRegExpValidator(QRegExp ("[^!@#$%^&*()_]"));

//QRegExpValidator*  validator = new QRegExpValidator(QRegExp ("[a-zA-Z0-9]{0,2}"));


//    this->setValidator(validator);
//for(int i=0;i<10;i++)
//    this->addItem(QString::number(i));

}

void my_combobox::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu* menu=this->lineEdit()->createStandardContextMenu();

        for(int i=0;i<menu->actions().count();i++)
        {
    QAction* action=menu->actions().at(i);
    //qDebug()<<i<<" "<<action->text();
    }
    menu->actions().at(0)->setText("Отмена\tCtrl+Z");
    menu->actions().at(1)->setText("Вернуть\tCtrl+Y");
    menu->actions().at(3)->setText("Вырезать\tCtrl+X");
    menu->actions().at(4)->setText("Копировать\tCtrl+C");
    menu->actions().at(5)->setText("Вставить\tCtrl+V");
    menu->actions().at(6)->setText("Удалить");
    menu->actions().at(8)->setText("Выбрать все\tCtrl+A");

      menu->exec(event->globalPos());
}

