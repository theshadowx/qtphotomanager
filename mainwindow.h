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
#include "dialogproperties.h"

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /*!
    * Constructs a MainWindow with the given parent.
    */
    explicit MainWindow(QWidget *parent=0);
    /*!
     * Destroys the main window.
     */
    ~MainWindow();


protected:
    /*!
    *   This event handler can be reimplemented in a subclass to receive widget resize events which are passed in the event parameter. When resizeEvent() is called,
    *   the widget already has its new geometry. The old size is accessible through QResizeEvent::oldSize().
    *
    *   The widget will be erased and receive a paint event immediately after processing the resize event. No drawing need be (or should be) done inside this handler.
    */
    virtual void resizeEvent(QResizeEvent* );

private:
    QMenu          *fileMenu;
    QMenu          *editMenu;
    QMenu          *helpMenu;

    QAction        *logoutAct;
    QAction        *quitAct;
    QAction        *aboutAct;
    QAction        *aboutQtAct;

    QMenuBar       *menuBar;
    QStatusBar     *statusBar;
    ConfWidget     *confWidget;
    SortWidget     *sortWidget;
    GraphicsView   *view;

    Ui::MainWindow  *ui;
    Users           *currentUser;
    UsersChain      *userChain;
    ImageCellChain  *imageCellChain;
    DataBase        *database;


signals:
    void cellItemClicked();

private slots:
    /*!
    *   Checks whether a user, with the username and the password given, exists in the database.
    *   If so, the user accedes to the application, otherwise an error message pops up, telling
    *   that no user exists in the database with the givent username and password.
    */
    void on_connectButton_clicked();
    /*!
    *   Verify that the entries for the new user are correct and that there is no user in database with the username given.
    *   If all is correct the user's entries are added to the database with default permission level 2. Then the new user
    *   accedes directly to the application.
    */
    void on_submitBut_clicked();
    /*!
    *   This function is called when the user click on the mouse left button.
    *   If an image is clicked then a menu shows up with 3 options (process the image, delete an image, insert images).
    *   If not an image, the menu will show just "insert images".
    *
    *   When the option "process the image" is selected then the user will be launched to the processing window.
    *
    *   When the option "delete the image" is selected then the image will be deleted from the database.
    *
    *   When the option "insert images" is selected then a file browser will show up.
    *   The user will have whether to select one image or many images or just to cancel.
    *   In the first two cases the images are added to the database.
    */
    void showContextMenu(const QPoint &pos);
    /*!
    *   This function will call on_connectButton_clicked() when the user click on the return key while he is logging in.
    */
    void clickEnterLogin();
    /*!
    *   This function will call on_submitBut_clicked() when the user click on the return key while he is registerring.
    */
    void clickEnterRegister();
    /*!
     * This function is called when an image is clicked.
     * It hides the global scene and sortwidget and shows sceneProcessed and confwidget
     */
    void onCellItemclicked(CellItem *item);
    /*!
    *   The user will be logged out.
    */
    void logOut();
    /*!
    *   This will show information about the application.
    */
    void about();
    /*!
    *   This will show information about the Qt used.
    */
    void aboutQt();

};

#endif // MAINWINDOW_H
