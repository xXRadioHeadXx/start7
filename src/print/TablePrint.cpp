#include "TablePrint.h"

#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QTextBrowser>
#include <QPrinter>
#include <QPrintPreviewDialog>
#include <QPrintDialog>
#include <QDateTime>
#include <QFileInfo>
#include <QTableView>
#include <QTextDocument>


TablePrint::TablePrint(QObject *parent) : QObject(parent)
{

}

bool TablePrint::prepareTmpFileHtmlTableFromModel(const QTableView *tableView) {
    QString strStream;
    QTextStream out(&strStream);

    const int rowCount = tableView->model()->rowCount();
    const int columnCount = tableView->model()->columnCount();

    out <<  "<html>\n"
        "<head>\n"
        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
        <<  QString("<title>%1</title>\n").arg(tr("Отчёт"))
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

    out << "<table border=\"0\" bordercolor=\"#ffffff\" cellspacing=\"1\" cellpadding= \"1\" align=\"right\" cols=\"2\" width=\"45%\">"
           "    <tr>"
           "        <td width=\"50%\">&nbsp;</td>"
           "        <td width=\"50%\">&nbsp;</td>"
           "    </tr>"
           "    <tr>"
           "        <td width=\"50%\"><hr></td>"
           "        <td width=\"50%\"><hr></td>"
           "    </tr>"
           "    <tr>"
           "        <td align=\"center\">" << tr("подпись") << "</td>"
           "        <td align=\"center\">" << tr("ФИО") << "</td>"
           "    </tr>"
           "        <tr>"
           "        <td width=\"50%\">" << QDateTime::currentDateTime().toString("dd.MM.yyyy \t hh:mm:ss") << "&nbsp;</td>"
           "        <td width=\"50%\">&nbsp;</td>"
           "    </tr>"
           "    <tr>"
           "        <td><hr></td>"
           "        <td></td>"
           "    </tr>"
           "    <tr>"
           "        <td align=\"center\">" << tr("дата, время создания") << "</td>"
           "        <td></td>"
           "    </tr>"
           "</table>";

    //qDebug() << strStream;


    if(QFile::exists("tmpprint"))
        QFile::remove("tmpprint");

    QFile tmpf("tmpprint");
    if (!tmpf.open(QIODevice::WriteOnly | QIODevice::Text)) {
        //qDebug() << "Can`t create file tmpprint";
        return false;
    } else {
        QTextStream fout(&tmpf);
        fout << strStream;
        tmpf.close();
    }

    return true;
}

bool TablePrint::print()
{
    QTextDocument *loc_document = new QTextDocument();
    QFile tmpf("tmpprint");
    if (!tmpf.open(QIODevice::ReadOnly | QIODevice::Text)) {
        //qDebug() << "Can`t read file tmpprint";
        delete loc_document;
        return false;
    } else {
        QTextStream sin(&tmpf);
        loc_document->setHtml(sin.readAll());
        tmpf.close();
    }

    QPrinter printer;

    QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
    if (dialog->exec() == QDialog::Accepted) {
        loc_document->print(&printer);
    }

    delete dialog;
    delete loc_document;
    return true;
}

bool TablePrint::printPdf()
{
    QTextDocument loc_document;
    QFile tmpf("tmpprint");
    if (!tmpf.open(QIODevice::ReadOnly | QIODevice::Text)) {
        //qDebug() << "Can`t read file tmpprint";
        return false;
    } else {
        QTextStream sin(&tmpf);
        loc_document.setHtml(sin.readAll());
        tmpf.close();
    }

    QString filename = QFileDialog::getSaveFileName(nullptr, "Open File",QString(),"Pdf File(*.pdf)");
    //qDebug()<<"Print file name is "<<filename;
    if(!filename.isEmpty()) {
        if(QFileInfo(filename).suffix().isEmpty())
            filename.append(".pdf");
    } else
        return false;


//    printHtmlView = new QWebView;
//    connect(printHtmlView, SIGNAL(loadFinished(bool)), this, SLOT(htmlRender()));

//    printHtmlView->setHtml(html);


    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPageSize(QPageSize(QPageSize::A4));
    printer.setOutputFileName(filename);
    printer.setPageMargins(QMarginsF(15, 15, 15, 15));

    loc_document.print(&printer);
    return true;
}

bool TablePrint::printPreview()
{
    document = new QTextDocument();
    QFile tmpf("tmpprint");
    if (!tmpf.open(QIODevice::ReadOnly | QIODevice::Text)) {
        //qDebug() << "Can`t read file tmpprint";
        return false;
    } else {
        QTextStream sin(&tmpf);
        document->setHtml(sin.readAll());
        tmpf.close();
    }

    QPrinter printer(QPrinter::ScreenResolution);
    printer.setPageSize(QPageSize(QPageSize::A4));
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName( "tmpprint_out" );
    // printer.setPageMargins(0.925, 0.8, 0.5, 0.8, QPrinter::Inch);

    QSizeF paperSize;
    paperSize.setWidth(printer.width());
    paperSize.setHeight(printer.height());
    document->setPageSize(paperSize); // the document needs a valid PageSize

    document->print(&printer);

    QPrintPreviewDialog *dialog = new QPrintPreviewDialog(&printer, NULL);

    connect(dialog, SIGNAL(paintRequested(QPrinter *)), this, SLOT(slotPreview(QPrinter *)));

    if (dialog->exec() == QDialog::Accepted) {
        document->print(&printer);
    }    

    return true;
}

void TablePrint::slotPreview(QPrinter *p)
{
    document->print(p);
}

//void TablePrint::htmlRender()
//{
//   QPrinter printer;
//   printer.setOutputFormat(QPrinter::PdfFormat);
//   printer.setOutputFileName(pdfPath); // устанавливаем путь к pdf файлу
//   printHtmlView->print(&printer);
//   //printHtmlView->show(); // хотим ли мы посмотреть что вышло?
//}
