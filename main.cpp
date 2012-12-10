#include <QtGui/QApplication>
#include "database.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
/*
    if (!createConnection())
        return 1;
*/
    MainWindow w;
    w.setWindowTitle("PhotoManager (beta)");
    w.show();

    return a.exec();
}

