#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtCore>
#include "graphicsview.h"
#include "database.h"
#include "confwidget.h"
#include "sortwidget.h"
#include "userschain.h"
#include "imagecellchain.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent=0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_submitBut_clicked();
    void showContextMenu(const QPoint &pos);

    void logOut();
    void about();
    void aboutQt();


private:

    QMenu          *fileMenu;
    QMenu          *editMenu;
    QMenu          *helpMenu;
    QActionGroup   *alignmentGroup;
    QAction        *logoutAct;
    QAction        *quitAct;
    QAction        *aboutAct;
    QAction        *aboutQtAct;
    QLabel         *infoLabel;

    QMenuBar       *menuBar;
    QStatusBar     *statusBar;
    QLabel         *zoomLabel;
    ConfWidget     *confWidget;
    SortWidget     *sortWidget;
    graphicsView   *view;


    Ui::MainWindow *ui;
    Users *currentUser;
    UsersChain *userChain;
    ImageCellChain * imageCellChain;
    DataBase *database;

    void onCellItemclicked(CellItem *item);

protected:

    virtual bool eventFilter(QObject * obj, QEvent *event);
    virtual void resizeEvent(QResizeEvent* );


};

#endif // MAINWINDOW_H
