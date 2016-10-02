/**
 * @mainpage
 * @author Ali Diouri           <alidiouri@gmail.com> <br>
 *
 * @date February 2012
 */

#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/icon/qt-logo.png"));

    QFile qss(":/stylesheet/stylesheet.qss");
    qss.open(QFile::ReadOnly);
    a.setStyleSheet(qss.readAll());
    qss.close();

    MainWindow w;
    w.setWindowTitle("PhotoManager (beta)");
    w.show();

    return a.exec();
}







