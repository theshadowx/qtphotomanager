#include "mainwindow.h"
#include "ui_mainwindow.h"

/// Constructor of MainWindow
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    userChain = new UsersChain();
    imageCellChain = new ImageCellChain();
    database = new DataBase();

    nbTries = 0;
    currentUser = 0;

    Users *user = 0;

    /** *************** init interface ***************** **/
    ui->setupUi(this);

    menuBar = new QMenuBar(this);
    this->setMenuBar(menuBar);

    fileMenu = menuBar->addMenu(tr("&File"));
    quitAct = new QAction("&Quit", fileMenu);
    logoutAct = new QAction("&Log Out",fileMenu);
    fileMenu->addAction(logoutAct);
    fileMenu->addAction(quitAct);

    editMenu = menuBar->addMenu("&Edit");

    helpMenu = menuBar->addMenu("&Help");
    aboutAct = new QAction("A&bout", helpMenu);
    aboutQtAct = new QAction("Abo&ut Qt", helpMenu);
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);

    adminMenu = menuBar->addMenu("&Admin");
    userDBAct = new QAction("user DataBase",adminMenu);
    imageDBAct = new QAction("image DataBase",adminMenu);
    adminMenu->addAction(userDBAct);
    adminMenu->addAction(imageDBAct);
    adminMenu->menuAction()->setVisible(false);

    aboutAct->setShortcut(Qt::CTRL + Qt::Key_B);
    aboutQtAct->setShortcut(Qt::CTRL + Qt::Key_U);
    quitAct->setShortcut(Qt::CTRL+Qt::Key_Q);
    logoutAct->setShortcut(Qt::CTRL+Qt::Key_L);

    ui->centralWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    view = new GraphicsView(ui->centralWidget);
    view->scene->imageCellChain = imageCellChain;
    view->setGeometry(0,0,1250*3/4,750);
    view->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    view->hide();

    sortWidget = new SortWidget(ui->centralWidget);
    sortWidget->setGeometry(1250*3/4,0,1250*1/4,750);
    sortWidget->hide();

    confWidget = new ConfWidget(ui->centralWidget);
    confWidget->setGeometry(1250*3/4,0,1250*1/4,750);
    confWidget->view = view;
    confWidget->hide();

    /** ********* init dataBase/UsersChain ***************** **/

    int userNumLines = database->getUserNumlines();
    if(userNumLines != 0){
        for(int i=0; i<userNumLines; i++){
            user = database->getUserDb(i);
            userChain->addUser(user);
        }
    }else{
        Users *adminUser = new Users("admin","root",Users::LEVEL_1);
        userChain->addUser(adminUser);
        database->addUserDb(adminUser);
    }

    databaseWidget = new DatabaseWidget(database, ui->centralWidget);
    databaseWidget->setGeometry(0,0,1250,750);
    databaseWidget->hide();

    /** *************** Connection SLOT/SIGNAL ***************** **/

    QObject::connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
    QObject::connect(aboutQtAct, SIGNAL(triggered()), this, SLOT(aboutQt()));
    QObject::connect(quitAct, SIGNAL(triggered()), this, SLOT(close()));
    QObject::connect(logoutAct, SIGNAL(triggered()), this, SLOT(logOut()));
    QObject::connect(userDBAct, SIGNAL(triggered()), databaseWidget, SLOT(showUserDb()));
    QObject::connect(imageDBAct, SIGNAL(triggered()), databaseWidget, SLOT(showImageDb()));
    QObject::connect(confWidget, SIGNAL(cancelButtonClicked()), sortWidget, SLOT(show()));
    QObject::connect(confWidget, SIGNAL(saveButtonClicked()), sortWidget, SLOT(show()));
    QObject::connect(databaseWidget, SIGNAL(cancelButtonClicked()), sortWidget, SLOT(show()));
    QObject::connect(databaseWidget, SIGNAL(saveButtonClicked()), sortWidget, SLOT(show()));
    QObject::connect(databaseWidget, SIGNAL(imageDbChanged(DataBase*)), imageCellChain, SLOT(update(DataBase*)));
    QObject::connect(databaseWidget, SIGNAL(userDbChanged(DataBase*)), userChain, SLOT(update(DataBase*)));
    QObject::connect(imageCellChain, SIGNAL(updated()), view, SLOT(updateScene()));
    QObject::connect(this, SIGNAL(cellItemClicked()), confWidget , SLOT(showHistogram()));
    QObject::connect(view, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(showContextMenu(const QPoint&)));
    QObject::connect(view, SIGNAL(cellItemClicked(CellItem *)), this, SLOT(onCellItemclicked(CellItem *)));
    QObject::connect(ui->passwordEdit, SIGNAL(returnPressed()), this, SLOT(clickEnterLogin()));
    QObject::connect(ui->userNameEdit, SIGNAL(returnPressed()), this, SLOT(clickEnterLogin()));
    QObject::connect(ui->usrCnEdit, SIGNAL(returnPressed()), this, SLOT(clickEnterRegister()));
    QObject::connect(ui->pwCnEdit, SIGNAL(returnPressed()), this, SLOT(clickEnterRegister()));
    QObject::connect(ui->pwCfCnEdit, SIGNAL(returnPressed()), this, SLOT(clickEnterRegister()));
}

/// Destructor of MainWindow
MainWindow::~MainWindow()
{
    delete ui;
}

/// Login callBack
void MainWindow::on_connectButton_clicked()
{
    CellItem *cellItem = 0;

    QString username = ui->userNameEdit->text();
    QString password = ui->passwordEdit->text();

    ui->userNameEdit->setText("");
    ui->passwordEdit->setText("");

    if(username.isEmpty() || username.isEmpty()){
        QMessageBox msgBox;
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setText("Username or Password is empty, please retry.");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        this->activateWindow();
        ui->userNameEdit->setFocus();
        return;
    }else{
        currentUser = userChain->getUser(username,password);
        if(currentUser){
            nbTries = 3;
            view->currentUser = currentUser;
            if(currentUser->getPermission() != Users::LEVEL_3){
                ui->connectionWidget->hide();
                int imageNumLines = database->getImageNumlines();

                for(int i=0; i<imageNumLines; i++){
                    cellItem = database->getImageDb(i);
                    if(currentUser->getPermission() == Users::LEVEL_1){
                        imageCellChain->addCellItem(cellItem);
                        view->scene->addItem(cellItem);
                    }else if(cellItem->getImageCfdy() == CellItem::F){
                        imageCellChain->addCellItem(cellItem);
                        view->scene->addItem(cellItem);
                    }
                }

                if(currentUser->getUsername() == "admin"){
                    adminMenu->menuAction()->setVisible(true);
                }

                view->adjustCellItems();
                view->show();
                sortWidget->show();
            }else{
                QMessageBox msgBox;
                msgBox.setStandardButtons(QMessageBox::Ok);
                msgBox.setText("Your account has not been activated yet");
                msgBox.setIcon(QMessageBox::Critical);
                msgBox.exec();
            }
        }else{
            nbTries ++;
            if(nbTries < 3){
                QMessageBox msgBox;
                msgBox.setStandardButtons(QMessageBox::Ok);
                msgBox.setText("Username or Password is wrong, please retry.");
                msgBox.setIcon(QMessageBox::Critical);
                msgBox.exec();
                this->activateWindow();
                ui->userNameEdit->setFocus();
            }else{
                ui->passwordEdit->setDisabled(true);
                ui->userNameEdit->setDisabled(true);
                ui->connectButton->setDisabled(true);
            }
        }
    }
}

/// Enter pressed callback (login fields)
void MainWindow::clickEnterLogin()
{
    on_connectButton_clicked();
}

/// Register callBack
void MainWindow::on_submitBut_clicked(){
    QString username = ui->usrCnEdit->text();
    QString password = ui->pwCnEdit->text();
    QString passwordconf = ui->pwCfCnEdit->text();

    ui->usrCnEdit->setText("");
    ui->pwCnEdit->setText("");
    ui->pwCfCnEdit->setText("");

    QMessageBox msgBox;
    msgBox.setStandardButtons(QMessageBox::Ok);

    if(password != passwordconf || password.isEmpty() || username.isEmpty()){
        msgBox.setText("The passwords are not the same or something is missing, please retry.");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        this->activateWindow();
        ui->usrCnEdit->setFocus();
        return;
    }else if(userChain->containsUser(username)){
        msgBox.setText("This username is not available, please retry.");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        this->activateWindow();
        ui->usrCnEdit->setFocus();
        return;
    }else{
        Users *user = new Users(username,password,Users::LEVEL_3);
        userChain->addUser(user);
        database->addUserDb(user);
        currentUser = user;
        msgBox.setText("Your account will be active after the Validation Service validate it");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.exec();
        this->activateWindow();
    }
}

/// Enter pressed callback (registering fields)
void MainWindow::clickEnterRegister()
{
    on_submitBut_clicked();
}

/// Mouse click (Right Button) callBack
void MainWindow::showContextMenu(const QPoint &pos)
{
    QPoint globalPos = view->mapToGlobal(pos);

    QMenu optionMenu(this);
    QAction processImageAction("Process this image",&optionMenu);
    QAction deleteImageAction("Delete this image",&optionMenu);
    QAction insertImageAction("insert an image",&optionMenu);
    QAction imagePropAction("Properties",&optionMenu);

    if(currentUser->getPermission() == Users::LEVEL_1){
        CellItem *item = static_cast<CellItem*> (view->scene->itemAt(view->mapToScene(pos)));
        if(view->QGraphicsView::scene() == view->scene){
            if(item!=NULL){
                optionMenu.addAction(&processImageAction);
                optionMenu.addAction(&deleteImageAction);
                optionMenu.addAction(&insertImageAction);
                optionMenu.addAction(&imagePropAction);
            }else{
                optionMenu.addAction(&insertImageAction);
            }

            QAction* selectedAction = optionMenu.exec(globalPos);
            if(selectedAction == &processImageAction){
                if(item!=NULL){
                    if(view->scene->imageCellChain->contains(item)){
                        onCellItemclicked(item);
                    }else{
                        CellItem *itemParent = static_cast<CellItem*> (item->parentItem());
                        onCellItemclicked(itemParent);
                    }
                }
            }else if(selectedAction == &deleteImageAction){
                CellItem *item = static_cast<CellItem*> (view->scene->itemAt(view->mapToScene(pos)));
                if(item!=NULL){
                    if(view->scene->imageCellChain->contains(item)){
                        database->deleteImageDb(item->getImageName());
                        view->scene->imageCellChain->deleteCellItem(item);
                    }else{
                        CellItem *itemParent = static_cast<CellItem*> (item->parentItem());
                        database->deleteImageDb(itemParent->getImageName());
                        view->scene->imageCellChain->deleteCellItem(itemParent);
                    }
                    view->adjustCellItems();
                }
            }else if(selectedAction == &insertImageAction){
                QStringList fileNames;
                QFileDialog dialog(this);
                dialog.setFileMode(QFileDialog::ExistingFiles);
                QFileInfo fileInfo;
                dialog.setNameFilter("Images (*.png *.bmp *.jpg)");
                if (dialog.exec()){
                    fileNames = dialog.selectedFiles();
                    for(int i=0; i<fileNames.count();i++){
                        fileInfo.setFile(fileNames.at(i));
                        if(!imageCellChain->contains(fileInfo.baseName()) && !fileInfo.baseName().contains(" ")){
                            CellItem *cellItem = new CellItem(imageCellChain->getCount(),
                                                              fileInfo.baseName(),
                                                              fileInfo.absolutePath(),
                                                              500,
                                                              QPixmap(fileInfo.absoluteFilePath()));
                            cellItem->setImageType(fileInfo.completeSuffix());
                            imageCellChain->addCellItem(cellItem);
                            database->addImageDb(cellItem);
                            view->scene->addItem(cellItem);
                        }
                    }
                view->adjustCellItems();
                }

            }else if(selectedAction == &imagePropAction){
                QGraphicsItem *item = view->scene->itemAt(view->mapToScene(pos));
                CellItem *cellItem = 0;

                if(view->scene->imageCellChain->contains(static_cast<CellItem*> (item))){
                   cellItem = static_cast<CellItem*> (item);
                }else{
                   cellItem = static_cast<CellItem*> (item->parentItem());
                }

                DialogProperties dialogProperties(cellItem,this);
                dialogProperties.exec();

            }
        }
    }
}

/// CellItem mouse click callBack
void MainWindow::onCellItemclicked(CellItem *item)
{
    if(currentUser->getPermission() == Users::LEVEL_1){
        QString strPath = item->getImagePath()+ QDir().separator() + item->getImageName()+ "." + item->getImageType();
        confWidget->matOriginal = cv::imread(strPath.toStdString());
        confWidget->matProcessed = cv::imread(strPath.toStdString());

        confWidget->resize(confWidget->parentWidget()->frameSize().width()*1/4,confWidget->parentWidget()->frameSize().height());
        confWidget->setGeometry(confWidget->parentWidget()->frameSize().width() * 3/4,0,confWidget->size().width(),confWidget->size().height());
        confWidget->pixOriginal = item->image->pixmap();

        sortWidget->hide();
        confWidget->show();

        emit cellItemClicked();
    }
}

/// Resize window event callBack
void MainWindow::resizeEvent(QResizeEvent*)
{
    ui->connectionWidget->setGeometry(0,0,ui->centralWidget->width(),ui->centralWidget->height());
    ui->frame->setGeometry(ui->centralWidget->frameGeometry().center().x()-ui->frame->width()/2,
                       ui->centralWidget->frameGeometry().center().y()-ui->frame->height()/2,
                       ui->frame->width(),
                       ui->frame->height());

    view->resize(ui->centralWidget->frameSize().width()*3/4,ui->centralWidget->frameSize().height());

    sortWidget->resize(ui->centralWidget->frameSize().width()*1/4,ui->centralWidget->frameSize().height());
    sortWidget->setGeometry(ui->centralWidget->frameSize().width() * 3/4, 0, sortWidget->size().width(), sortWidget->size().height());

    confWidget->resize(ui->centralWidget->frameSize().width()*1/4,ui->centralWidget->frameSize().height());
    confWidget->setGeometry(ui->centralWidget->frameSize().width() * 3/4,0,confWidget->size().width(), confWidget->size().height());

    if(!view->isHidden()){
        if(view->QGraphicsView::scene() == view->scene){
            view->adjustCellItems();
            sortWidget->show();
        }else if(view->QGraphicsView::scene() == view->sceneProcessing){
            view->fitInView(view->sceneProcessing->cellItemSelected->image,Qt::KeepAspectRatio);
            confWidget->show();
        }
    }
    databaseWidget->resize(ui->centralWidget->frameSize().width(),ui->centralWidget->frameSize().height());
}

/// Logout menu action callback
void MainWindow::logOut()
{
    currentUser = 0;
    adminMenu->menuAction()->setVisible(false);
    view->currentUser = 0;
    view->hide();
    confWidget->hide();
    sortWidget->hide();
    ui->connectionWidget->show();
    for(int i=imageCellChain->getCount()-1; i>=0;i--)
        imageCellChain->deleteCellItemAt(i);
}

/// About menu action callback
void MainWindow::about(){
    QMessageBox msgBox;
    msgBox.setWindowTitle("About");
    msgBox.addButton(QMessageBox::Ok);
    msgBox.setText("<p align='center'>PhotoManager<br>"
                        "Version 0.1<br>"
                        "By Ali Diouri<br>"
                      "ali.diouri@gmail.com<br>"
               "Licensed under a Creative Commons Attribution 3.0 License</p>");
    msgBox.setIcon(QMessageBox::Information);
    int selection = msgBox.exec();
    if(selection == QMessageBox::Yes) {
        this->activateWindow();
    }
}

/// AboutQt menu action callback
void MainWindow::aboutQt()
{
    QMessageBox::aboutQt(this, "About Qt");
}

