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

    /// *************** init interface ***************** ///
    ui->setupUi(this);

    menuBar = new QMenuBar(this);
    this->setMenuBar(menuBar);

    fileMenu = menuBar->addMenu(tr("&File"));
    quitAct = new QAction("&Quit", fileMenu);
    logoutAct = new QAction("&Log Out",fileMenu);
    fileMenu->addAction(logoutAct);
    fileMenu->addAction(quitAct);

    editMenu = menuBar->addMenu("&Edit");

    dbMenue = menuBar->addMenu("&Database");
    userDBAct = new QAction("user DataBase",dbMenue);
    imageDBAct = new QAction("image DataBase",dbMenue);
    dbMenue->addAction(userDBAct);
    dbMenue->addAction(imageDBAct);
    dbMenue->menuAction()->setVisible(false);

    helpMenu = menuBar->addMenu("&Help");
    aboutAct = new QAction("A&bout", helpMenu);
    aboutQtAct = new QAction("Abo&ut Qt", helpMenu);
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);

    aboutAct->setShortcut(Qt::CTRL + Qt::Key_B);
    aboutQtAct->setShortcut(Qt::CTRL + Qt::Key_U);
    quitAct->setShortcut(Qt::CTRL+Qt::Key_Q);
    logoutAct->setShortcut(Qt::CTRL+Qt::Key_L);

    view = new GraphicsView(ui->centralWidget);
    view->imageCellChain = imageCellChain;
    view->installEventFilter(this);
    view->hide();

    sortWidget = new SortWidget(ui->centralWidget);
    sortWidget->imageCellChain = imageCellChain;

    sortWidget->view = view;
    sortWidget->hide();

    confWidget = new ConfWidget(ui->centralWidget);
    confWidget->view = view;
    confWidget->hide();

    previewWidget = new PreviewWidget(ui->centralWidget);
    previewWidget->imageCellChain = imageCellChain;
    previewWidget->hide();

    statusBarLabel= new QLabel(this);
    statusBar = new QStatusBar(this);
    statusBar->addPermanentWidget(statusBarLabel,500);
    this->setStatusBar(statusBar);

    /// ********* init dataBase(users)/UsersChain ***************** ///

    int userNumLines = database->getUserNumlines();
    if(userNumLines != 0){
        for(int i=0; i<userNumLines; i++){
            user = database->getUserDb(i);
            userChain->addUser(user);
        }
    }else{
        Users *adminUser = new Users("admin","root",Users::LEVEL_1,"admin@photomanager.org");
        userChain->addUser(adminUser);
        database->addUserDb(adminUser);
    }

    databaseWidget = new DatabaseWidget(database, ui->centralWidget);
    databaseWidget->hide();

    /// *************** Connection SLOT/SIGNAL ***************** ///

    QObject::connect(this, SIGNAL(authentificationOK()), view , SLOT(show()));
    QObject::connect(this, SIGNAL(authentificationOK()), sortWidget , SLOT(show()));
    QObject::connect(this, SIGNAL(authentificationOK()), ui->connectionWidget , SLOT(hide()));

    QObject::connect(this, SIGNAL(previewImage()), view , SLOT(hide()));
    QObject::connect(this, SIGNAL(previewImage()), sortWidget , SLOT(hide()));
    QObject::connect(this, SIGNAL(previewImage()), previewWidget , SLOT(show()));

    QObject::connect(this, SIGNAL(cellItemClicked()), confWidget , SLOT(drawHistogram()));
    QObject::connect(this, SIGNAL(cellItemClicked()), confWidget , SLOT(show()));
    QObject::connect(this, SIGNAL(cellItemClicked()), sortWidget , SLOT(hide()));

    QObject::connect(this, SIGNAL(processActionChosen(CellItem*)), view , SLOT(setupProcessingMode(CellItem*)));
    QObject::connect(this, SIGNAL(imageDbChanged()), databaseWidget , SLOT(updateImageTable()));
    QObject::connect(this, SIGNAL(userDbChanged()), databaseWidget , SLOT(updateUserTable()));

    QObject::connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
    QObject::connect(aboutQtAct, SIGNAL(triggered()), this, SLOT(aboutQt()));
    QObject::connect(quitAct, SIGNAL(triggered()), this, SLOT(close()));
    QObject::connect(logoutAct, SIGNAL(triggered()), this, SLOT(logOut()));

    QObject::connect(logoutAct, SIGNAL(triggered()), view, SLOT(hide()));
    QObject::connect(logoutAct, SIGNAL(triggered()), confWidget, SLOT(hide()));
    QObject::connect(logoutAct, SIGNAL(triggered()), sortWidget, SLOT(hide()));
    QObject::connect(logoutAct, SIGNAL(triggered()), databaseWidget, SLOT(hide()));
    QObject::connect(logoutAct, SIGNAL(triggered()), previewWidget, SLOT(hide()));
    QObject::connect(logoutAct, SIGNAL(triggered()), ui->connectionWidget, SLOT(show()));

    QObject::connect(userDBAct, SIGNAL(triggered()), databaseWidget, SLOT(showUserDb()));

    QObject::connect(imageDBAct, SIGNAL(triggered()), databaseWidget, SLOT(showImageDb()));

    QObject::connect(confWidget, SIGNAL(cancelButtonClicked()), view, SLOT(setupGlobalMode()));
    QObject::connect(confWidget, SIGNAL(cancelButtonClicked()), sortWidget, SLOT(show()));
    QObject::connect(confWidget, SIGNAL(cancelButtonClicked()), sortWidget, SLOT(sortImages()));
    QObject::connect(confWidget, SIGNAL(saveButtonClicked()), view, SLOT(setupGlobalMode()));
    QObject::connect(confWidget, SIGNAL(saveButtonClicked()), sortWidget, SLOT(show()));
    QObject::connect(confWidget, SIGNAL(saveButtonClicked()), sortWidget, SLOT(sortImages()));

    QObject::connect(previewWidget, SIGNAL(cancelButtonClicked()), view, SLOT(setupGlobalMode()));
    QObject::connect(previewWidget, SIGNAL(cancelButtonClicked()), sortWidget, SLOT(show()));
    QObject::connect(previewWidget, SIGNAL(cancelButtonClicked()), sortWidget, SLOT(sortImages()));

    QObject::connect(databaseWidget, SIGNAL(imageDbChanged(DataBase*)), imageCellChain, SLOT(update(DataBase*)));
    QObject::connect(databaseWidget, SIGNAL(userDbChanged(DataBase*)), userChain, SLOT(update(DataBase*)));

    QObject::connect(imageCellChain, SIGNAL(updated()), view, SLOT(updateScene()));

    QObject::connect(view, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(showContextMenu(const QPoint&)));
    QObject::connect(view, SIGNAL(cellItemClicked(CellItem *)), this, SLOT(onCellItemclicked(CellItem *)));
    QObject::connect(view, SIGNAL(cellItemDeleted(QList<CellItem*>)), databaseWidget, SLOT(onImageDeleted(QList<CellItem*>)));

    QObject::connect(ui->passwordEdit, SIGNAL(returnPressed()), this, SLOT(clickEnterLogin()));
    QObject::connect(ui->userNameEdit, SIGNAL(returnPressed()), this, SLOT(clickEnterLogin()));
    QObject::connect(ui->usrCnEdit, SIGNAL(returnPressed()), this, SLOT(clickEnterRegister()));
    QObject::connect(ui->emailRegEdit, SIGNAL(returnPressed()), this, SLOT(clickEnterRegister()));
    QObject::connect(ui->emailRegCfEdit, SIGNAL(returnPressed()), this, SLOT(clickEnterRegister()));
}

/// Destructor of MainWindow
MainWindow::~MainWindow()
{
    delete ui;
    delete imageCellChain;
    imageCellChain = 0;
    delete database;
    database = 0;
    delete userChain;
    userChain = 0;
}

/// Login callBack
void MainWindow::on_connectButton_clicked()
{
    CellItem *cellItem = 0;

    QString username = ui->userNameEdit->text();
    QString password = ui->passwordEdit->text();

    ui->userNameEdit->setText("");
    ui->passwordEdit->setText("");

    QMessageBox msgBox;
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setIcon(QMessageBox::Critical);

    if(username.isEmpty() || username.isEmpty()){
        msgBox.setText("Username or Password is empty, please retry.");
        msgBox.exec();
        this->activateWindow();
        ui->userNameEdit->setFocus();
        return;
    }else{
        currentUser = userChain->getUser(username,password);
        if(currentUser){
            nbTries = 0;
            view->currentUser = currentUser;
            if(currentUser->getPermission() != Users::LEVEL_3){
                database->setImageDB(username,currentUser->getPermission());
                int imageNumLines = database->getImageNumlines();
                if(currentUser->getPermission() == Users::LEVEL_1){
                    dbMenue->menuAction()->setVisible(true);
                    if(currentUser->getUsername() == "admin"){
                        userDBAct->setVisible(true);
                    }else{
                        userDBAct->setVisible(false);
                    }
                    for(int i=0; i<imageNumLines; i++){
                        cellItem = database->getImageDb(i);
                        imageCellChain->addCellItem(cellItem);
                        view->scene->addItem(cellItem);
                    }
                }else{
                    for(int i=0; i<imageNumLines; i++){
                        cellItem = database->getImageDb(i);
                        if(cellItem->getImageCfdy() == CellItem::F){
                            imageCellChain->addCellItem(cellItem);
                            view->scene->addItem(cellItem);
                        }
                    }
                }
                databaseWidget->updateImageTable();
                view->adjustCellItems();
                view->setFocus();
                emit authentificationOK();
            }else{
                msgBox.setText("Your account has not been activated yet");
                msgBox.exec();
            }
        }else{
            nbTries++;
            if(nbTries < 3){
                msgBox.setText("Username or Password is wrong, please retry.");
                msgBox.exec();
                this->activateWindow();
                ui->userNameEdit->setFocus();
            }else{
                ui->passwordEdit->setDisabled(true);
                ui->userNameEdit->setDisabled(true);
                ui->connectButton->setDisabled(true);

                msgBox.setText("Please contact the administrator. If you haven't registred yet, fill up the registration area");
                msgBox.exec();
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
    QString email = ui->emailRegEdit->text();
    QString emailconf = ui->emailRegCfEdit->text();

    ui->usrCnEdit->setText("");
    ui->emailRegEdit->setText("");
    ui->emailRegCfEdit->setText("");

    QMessageBox msgBox;
    msgBox.setStandardButtons(QMessageBox::Ok);

    if(email != emailconf || email.isEmpty() || username.isEmpty()){
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
        Users *user = new Users(username,"",Users::LEVEL_3,email);
        userChain->addUser(user);
        database->addUserDb(user);
        databaseWidget->updateUserTable();
        msgBox.setText(QString("Thank you for registering, %1. An email has been dispatched to %2 with details on how to activate your account").arg(username,email));
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
    CellItem *cellItem = 0;
    QPoint globalPos = view->mapToGlobal(pos);

    QMenu optionMenu(this);
    QAction processImageAction("Process this image",&optionMenu);
    QAction deleteImageAction("Delete this image",&optionMenu);
    QAction insertImageAction("insert an image",&optionMenu);
    QAction imagePropAction("Properties",&optionMenu);
    QAction previewImageAction("Preview",&optionMenu);

    if(currentUser->getPermission() == Users::LEVEL_1){
        CellItem *item = static_cast<CellItem*> (view->scene->itemAt(view->mapToScene(pos),  QTransform()));
        if(view->QGraphicsView::scene() == view->scene){
            if(item!=NULL){
                optionMenu.addAction(&previewImageAction);
                optionMenu.addAction(&processImageAction);
                optionMenu.addAction(&deleteImageAction);
                optionMenu.addAction(&insertImageAction);
                optionMenu.addAction(&imagePropAction);
            }else{
                optionMenu.addAction(&insertImageAction);
            }

            QAction* selectedAction = optionMenu.exec(globalPos);
            if(selectedAction == &previewImageAction){
                if(view->cellItemSelected){
                    view->cellItemSelected->setColor(QColor(255,255,255));
                    view->cellItemSelected = 0;
                }

                previewWidget->adjustCellItems();
                emit previewImage();

                if(view->imageCellChain->contains(static_cast<CellItem*> (item))){
                    cellItem = static_cast<CellItem*> (item);
                }else{
                    cellItem = static_cast<CellItem*> (item->parentItem());
                }
                previewWidget->cellItemSelected = cellItem;
                previewWidget->showImage(cellItem);
            }else if(selectedAction == &processImageAction){
                if(item!=NULL){
                    if(view->imageCellChain->contains(item)){
                        emit processActionChosen(item);
                    }else{
                        CellItem *itemParent = static_cast<CellItem*> (item->parentItem());
                        emit processActionChosen(itemParent);
                    }
                }
            }else if(selectedAction == &deleteImageAction){
                CellItem *item = static_cast<CellItem*> (view->scene->itemAt(view->mapToScene(pos), QTransform()));
                if(item!=NULL){
                    if(view->imageCellChain->contains(item)){
                        database->deleteImageDb(item->getImageName());
                        view->imageCellChain->deleteCellItem(item);
                    }else{
                        CellItem *itemParent = static_cast<CellItem*> (item->parentItem());
                        database->deleteImageDb(itemParent->getImageName());
                        view->imageCellChain->deleteCellItem(itemParent);
                    }
                    view->adjustCellItems();
                    databaseWidget->updateImageTable();
                }
            }else if(selectedAction == &insertImageAction){
                bool errorLoading = false;
                QStringList fileNames;
                QFileInfo fileInfo;
                QStringList filters;
                QFileDialog dialog(this);
                dialog.setFileMode(QFileDialog::ExistingFiles);
                filters << "Images (*.png *.bmp *.jpg *.jpeg)"
                        << "Images (*.jpg *.jpeg)"
                        << "Images (*.bmp)"
                        << "Images (*.png)";
                dialog.setNameFilters(filters);

                if (dialog.exec()){
                    fileNames = dialog.selectedFiles();
                    for(int i=0; i<fileNames.count();i++){
                        fileInfo.setFile(fileNames.at(i));
                        if(!imageCellChain->contains(fileInfo.baseName()) && !fileInfo.baseName().contains("\t")){
                            CellItem *cellItem = new CellItem(imageCellChain->getCount(),
                                                              fileInfo.completeBaseName(),
                                                              fileInfo.absolutePath(),
                                                              500,
                                                              QPixmap(fileInfo.absoluteFilePath()));
                            cellItem->setImageSize((CellItem::IMAGE_SIZE)8);
                            cellItem->setImageType(fileInfo.suffix());
                            imageCellChain->addCellItem(cellItem);
                            database->addImageDb(cellItem);
                            view->scene->addItem(cellItem);
                        }else{
                            errorLoading = true;
                        }
                    }
                    view->adjustCellItems();
                    databaseWidget->updateImageTable();
                }
                if(errorLoading){
                    errorLoading = false;
                    QMessageBox msgBox;
                    msgBox.setStandardButtons(QMessageBox::Ok);
                    msgBox.setText("Some images haven't been load."
                                   "\nWhether they have a tabulation space in their name"
                                   "\nor they have been already added");
                    msgBox.setIcon(QMessageBox::Information);
                    msgBox.exec();
                }
            }else if(selectedAction == &imagePropAction){
                CellItem *cellItem = 0;
                QGraphicsItem *item = view->scene->itemAt(view->mapToScene(pos), QTransform());

                if(view->imageCellChain->contains(static_cast<CellItem*> (item))){
                    cellItem = static_cast<CellItem*> (item);
                }else{
                    cellItem = static_cast<CellItem*> (item->parentItem());
                }
                DialogProperties dialogProperties(cellItem,this);
                dialogProperties.exec();
            }
        }
    }else if(currentUser->getPermission() == Users::LEVEL_2){
        CellItem *item = static_cast<CellItem*> (view->scene->itemAt(view->mapToScene(pos), QTransform()));
        if(view->QGraphicsView::scene() == view->scene){
            if(item!=NULL){
                CellItem *cellItem = 0;
                QGraphicsItem *item = view->scene->itemAt(view->mapToScene(pos), QTransform());
                optionMenu.addAction(&previewImageAction);
                optionMenu.addAction(&imagePropAction);
                QAction* selectedAction = optionMenu.exec(globalPos);

                if(selectedAction == &previewImageAction){
                    if(view->cellItemSelected){
                        view->cellItemSelected->setColor(QColor(255,255,255));
                        view->cellItemSelected = 0;
                    }
                    previewWidget->adjustCellItems();
                    emit previewImage();

                    if(view->imageCellChain->contains(static_cast<CellItem*> (item))){
                        cellItem = static_cast<CellItem*> (item);
                    }else{
                        cellItem = static_cast<CellItem*> (item->parentItem());
                    }
                    previewWidget->cellItemSelected = cellItem;
                    previewWidget->showImage(cellItem);
                }else if(selectedAction == &imagePropAction){
                    CellItem *cellItem = 0;
                    QGraphicsItem *item = view->scene->itemAt(view->mapToScene(pos), QTransform());

                    if(view->imageCellChain->contains(static_cast<CellItem*> (item))){
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
}

/// CellItem mouse click callBack
void MainWindow::onCellItemclicked(CellItem *item)
{
    if(currentUser->getPermission() == Users::LEVEL_1){
        QString strPath = item->getImagePath()+ QDir().separator() + item->getImageName()+ "." + item->getImageType();
        confWidget->matOriginal = cv::imread(strPath.toStdString());
        confWidget->matProcessed = cv::imread(strPath.toStdString());

        confWidget->pixOriginal = item->image->pixmap();

        emit cellItemClicked();
    }
}

/// Filter the events comming from view
bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if(!view->isHidden()){
        if(view->QGraphicsView::scene() == view->sceneProcessing){
            QSize imageSize = view->cellItemSelected->image->pixmap().size();
            statusBarLabel->setText(QString("%1x%2 %3%")
                                    .arg((int)imageSize.width())
                                    .arg((int)imageSize.height())
                                    .arg((int)(100*view->transform().m11())));
        }else if(view->QGraphicsView::scene() == view->scene){
            statusBarLabel->setText(QString("%1 images").arg((imageCellChain->getCount())));
        }
    }
    return QMainWindow::eventFilter(obj, event);
}

/// Resize window event callBack
void MainWindow::resizeEvent(QResizeEvent*)
{
    ui->connectionWidget->setGeometry(0,0,ui->centralWidget->width(),ui->centralWidget->height());
    ui->frame->setGeometry(ui->centralWidget->frameGeometry().center().x()-ui->frame->width()/2,
                           ui->centralWidget->frameGeometry().center().y()-ui->frame->height()/2,
                           ui->frame->width(),
                           ui->frame->height());

    view->resize(ui->centralWidget->frameSize().width()-300,ui->centralWidget->frameSize().height());
    databaseWidget->resize(ui->centralWidget->frameSize().width(),ui->centralWidget->frameSize().height());
    previewWidget->resize(ui->centralWidget->frameSize().width(),ui->centralWidget->frameSize().height());
    sortWidget->setGeometry(ui->centralWidget->frameSize().width()-300, 0, 300, ui->centralWidget->frameSize().height());
    confWidget->setGeometry(ui->centralWidget->frameSize().width() -300,0,300, ui->centralWidget->frameSize().height());
}

/// Logout menu action callback
void MainWindow::logOut()
{
    nbTries = 0;
    currentUser = 0;
    statusBarLabel->setText("");
    view->currentUser = 0;
    dbMenue->menuAction()->setVisible(false);
    for(int i=imageCellChain->getCount()-1; i>=0;i--)
        imageCellChain->deleteCellItemAt(i);
    database->closeImageDb();
}

/// Update status bar
void MainWindow::updateStatusBar()
{
    if(view->QGraphicsView::scene() == view->sceneProcessing){
        QSize imageSize = view->cellItemSelected->image->pixmap().size();
        statusBarLabel->setText(QString("%1x%2 %3%")
                                .arg((int)imageSize.width())
                                .arg((int)imageSize.height())
                                .arg((int)(100*view->transform().m11())));
    }else if(view->QGraphicsView::scene() == view->scene){
        statusBarLabel->setText(QString("%1 images").arg((imageCellChain->getCount())));
    }
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

