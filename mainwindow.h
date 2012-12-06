#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtCore>
#include "graphicsview.h"
#include "database.h"
#include "confwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(const QString &usersTable, const QString &imagesTable,QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_pushButton_clicked();
    void on_submitBut_clicked();

    void about();
    void aboutQt();


private:


    QDir            dirPath;
    QSqlDatabase    db;
    QSqlQuery*      query;

    QMenu          *fileMenu;
    QMenu          *editMenu;
    QMenu          *helpMenu;
    QActionGroup   *alignmentGroup;
    QAction        *quitAct;
    QAction        *aboutAct;
    QAction        *aboutQtAct;
    QLabel         *infoLabel;

    QMenuBar       *menuBar;
    QStatusBar     *statusBar;
    QLabel         *zoomLabel;
    ConfWidget     *confWidget;
    graphicsView   *view;



    Ui::MainWindow *ui;
    QSqlTableModel *userTable;
    QSqlTableModel *imageTable;

protected:

   virtual void resizeEvent(QResizeEvent* );

};

#endif // MAINWINDOW_H
