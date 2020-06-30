#include "TablePrint.h"

#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QTextBrowser>
#include <QPrinter>
#include <QPrintPreviewDialog>
#include <QPrintDialog>

TablePrint::TablePrint(QObject *parent) : QObject(parent)
{

}

bool TablePrint::createHtmlTableFromModel(const QTableView *tableView) {
    QString strStream;
    QTextStream out(&strStream);

    const int rowCount = tableView->model()->rowCount();
    const int columnCount = tableView->model()->columnCount();

    out <<  "<html>\n"
        "<head>\n"
        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
        <<  QString("<title>%1</title>\n").arg(trUtf8("Отчёт"))
        <<  "</head>\n"
        "<body bgcolor=#ffffff link=#5000A0>\n"
        "<table border=1 cellspacing=0 cellpadding=2>\n";

    // headers
    out << "<thead><tr bgcolor=#f0f0f0>";
    for (int column = 0; column < columnCount; column++)
        if (!tableView->isColumnHidden(column))
            out << QString("<th>%1</th>").arg(tableView->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";

    // data table
    for (int row = 0; row < rowCount; row++) {
        out << "<tr>";
        for (int column = 0; column < columnCount; column++) {
            if (!tableView->isColumnHidden(column)) {
                QString data = tableView->model()->data(tableView->model()->index(row, column)).toString().simplified();
                out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }
    out <<  "</table>\n"
        "</body>\n"
        "</html>\n";

    qDebug() << strStream;

    QTextDocument *document = new QTextDocument();
    document->setHtml(strStream);



    QPrinter printer;

    QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
    if (dialog->exec() == QDialog::Accepted) {
        document->print(&printer);
    }

    delete document;
    return true;
}

void TablePrint::print()
{
//#ifndef QT_NO_PRINTER
//    QTextBrowser *editor = static_cast<QTextBrowser* >(textBrowser);
//    QPrinter printer;

//    QPrintDialog *dialog = new QPrintDialog(&printer, this);
//    dialog->setWindowTitle(tr("Print Document"));
//    if (editor->textCursor().hasSelection())
//        dialog->addEnabledOption(QAbstractPrintDialog::PrintSelection);
//    if (dialog->exec() != QDialog::Accepted)
//        return;

//    editor->print(&printer);
//#endif
}
