#include <QtGui/QApplication>
#include "database.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile qss("/home/theshadowx7/workspace/Project_QT/PhotoManager/stylesheet.qss");
    qss.open(QFile::ReadOnly);
    a.setStyleSheet(qss.readAll());
    qss.close();

    MainWindow w;
    w.setWindowTitle("PhotoManager (beta)");
    w.show();

    return a.exec();
}





