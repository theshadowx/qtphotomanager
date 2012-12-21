#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    userChain = new UsersChain();
    imageCellChain = new ImageCellChain();
    database = new DataBase();

    currentUser = 0;

    Users *user = 0;
    CellItem *cellItem = 0;

    /***************** init interface *******************/

    ui->setupUi(this);

    menuBar     = new QMenuBar(this);
    quitAct     = new QAction("&Quit", this);
    logoutAct   = new QAction("&Log Out",this);
    aboutAct    = new QAction("A&bout", this);
    aboutQtAct  = new QAction("Abo&ut Qt", this);

    aboutAct->setShortcut(Qt::CTRL + Qt::Key_B);
    aboutQtAct->setShortcut(Qt::CTRL + Qt::Key_U);
    quitAct->setShortcut(Qt::CTRL+Qt::Key_Q);
    logoutAct->setShortcut(Qt::CTRL+Qt::Key_L);


    fileMenu = menuBar->addMenu(tr("&File"));
    fileMenu->addAction(logoutAct);
    fileMenu->addAction(quitAct);

    editMenu = menuBar->addMenu(tr("&Edit"));

    helpMenu = menuBar->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);

    this->setMenuBar(menuBar);

    ui->centralWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    view = new graphicsView(ui->centralWidget);
    view->scene->imageCellChain = imageCellChain;
    view->setGeometry(0,0,1250*3/4,750);
    view->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    view->installEventFilter(this);
    view->hide();

    sortWidget = new SortWidget(ui->centralWidget);
    sortWidget->setGeometry(1250*3/4,0,1250*1/4,750);
    sortWidget->hide();

    confWidget = new ConfWidget(ui->centralWidget);
    confWidget->setGeometry(1250*3/4,0,1250*1/4,750);
    confWidget->view = view;
    confWidget->hide();

    /*********** init dataBase/UsersChain *******************/

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


    int imageNumLines = database->getImageNumlines();
    if(imageNumLines != 0){
        for(int i=0; i<imageNumLines; i++){
            cellItem = database->getImageDb(i);
            imageCellChain->addCellItem(cellItem);
            view->scene->addItem(cellItem);
        }
    }
    /***************** Connection SLOT/SIGNAL *******************/

    QObject::connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
    QObject::connect(aboutQtAct, SIGNAL(triggered()), this, SLOT(aboutQt()));
    QObject::connect(quitAct, SIGNAL(triggered()), this, SLOT(close()));
    QObject::connect(logoutAct, SIGNAL(triggered()), this, SLOT(logOut()));
    QObject::connect(confWidget, SIGNAL(cancelButton_clicked()), sortWidget, SLOT(show()));
    QObject::connect(confWidget, SIGNAL(saveButton_clicked()), sortWidget, SLOT(show()));
    QObject::connect(this, SIGNAL(cellItemClicked()), confWidget , SLOT(showHistogram()));
    QObject::connect(view, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(showContextMenu(const QPoint&)));
    QObject::connect(ui->passwordEdit, SIGNAL(returnPressed()), this, SLOT(clickEnterLogin()));
    QObject::connect(ui->userNameEdit, SIGNAL(returnPressed()), this, SLOT(clickEnterLogin()));
    QObject::connect(ui->usrCnEdit, SIGNAL(returnPressed()), this, SLOT(clickEnterRegister()));
    QObject::connect(ui->pwCnEdit, SIGNAL(returnPressed()), this, SLOT(clickEnterRegister()));
    QObject::connect(ui->pwCfCnEdit, SIGNAL(returnPressed()), this, SLOT(clickEnterRegister()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Login CallBack
void MainWindow::on_connectButton_clicked()
{
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
            ui->connectionWidget->hide();
            view->adjustCellItems();
            view->show();
            sortWidget->show();
        }else{
            QMessageBox msgBox;
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.setText("Username or Password is wrong, please retry.");
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.exec();
            this->activateWindow();
            ui->userNameEdit->setFocus();
        }
    }

}

// Register CallBack
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
        Users *user = new Users(username,password,Users::LEVEL_2);
        userChain->addUser(user);
        database->addUserDb(user);
        currentUser = user;
        view->adjustCellItems();
        view->show();
        sortWidget->show();
        ui->connectionWidget->hide();
        msgBox.setText("User added");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.exec();
        this->activateWindow();
    }
}

// View mouse click (Left Button) event filter
bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress)
    {
        if(currentUser->getPermission()==1){
            QMouseEvent* mouseEvent = static_cast<QMouseEvent*> (event);
            if(view->QGraphicsView::scene() == view->scene){
                if(mouseEvent->button() == Qt::LeftButton){
                    CellItem *item = static_cast<CellItem*> (view->scene->itemAt(view->mapToScene(mouseEvent->pos())));
                    if(item!=NULL){
                        if(view->scene->imageCellChain->contains(item)){
                            onCellItemclicked(item);
                        }else{
                            CellItem *itemParent = static_cast<CellItem*> (item->parentItem());
                            onCellItemclicked(itemParent);
                        }
                    }
                }
            }
        }
    }
    return QMainWindow::eventFilter(obj, event);
}

// Mouse click (Right Button) CallBack
void MainWindow::showContextMenu(const QPoint &pos)
{
    QPoint globalPos = view->mapToGlobal(pos);

    QMenu optionMenu(this);
    QAction processImageAction("Process this image",&optionMenu);
    QAction deleteImageAction("Delete this image",&optionMenu);
    QAction insertImageAction("insert an image",&optionMenu);

    if(currentUser->getPermission()==1){
        if(view->QGraphicsView::scene()==view->scene){
            if(view->scene->itemAt(view->mapToScene(pos))!=NULL){
                optionMenu.addAction(&processImageAction);
                optionMenu.addAction(&deleteImageAction);
                optionMenu.addAction(&insertImageAction);
            }else{
                optionMenu.addAction(&insertImageAction);
            }

            QAction* selectedOption = optionMenu.exec(globalPos);

            if(selectedOption == &processImageAction){
                CellItem *item = static_cast<CellItem*> (view->scene->itemAt(view->mapToScene(pos)));
                if(item!=NULL){
                    if(view->scene->imageCellChain->contains(item)){
                        onCellItemclicked(item);
                    }else{
                        CellItem *itemParent = static_cast<CellItem*> (item->parentItem());
                        onCellItemclicked(itemParent);
                    }
                }
            }else if(selectedOption == &deleteImageAction){
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
            }else if(selectedOption == &insertImageAction){
                QStringList fileNames;
                QFileDialog dialog(this);
                dialog.setFileMode(QFileDialog::ExistingFiles);
                QFileInfo fileInfo;
                dialog.setNameFilter("Images (*.png *.bmp *.jpg)");
                if (dialog.exec()){
                    fileNames = dialog.selectedFiles();
                    for(int i=0; i<fileNames.count();i++){
                        fileInfo.setFile(fileNames.at(i));
                        CellItem *cellItem = new CellItem(i,
                                                          fileInfo.baseName(),
                                                          fileInfo.absolutePath(),
                                                          500,
                                                          QPixmap(fileInfo.absoluteFilePath()));
                        cellItem->setImageType(fileInfo.completeSuffix());
                        imageCellChain->addCellItem(cellItem);
                        database->addImageDb(cellItem);
                        view->scene->addItem(cellItem);
                    }
                view->adjustCellItems();
                }

            }
        }
    }
}

void MainWindow::clickEnterLogin()
{
    on_connectButton_clicked();
}

void MainWindow::clickEnterRegister()
{
    on_submitBut_clicked();
}

// CellItem mouse click CallBack
void MainWindow::onCellItemclicked(CellItem *item)
{
    view->scene->cellItemSelected  = item;
    view->resize(view->parentWidget()->size().width()*3/4,view->parentWidget()->size().height());
    view->setScene(view->sceneProcessing);
    view->scene->removeItem(view->scene->cellItemSelected);
    view->sceneProcessing->addItem(view->scene->cellItemSelected->image);
    view->sceneProcessing->cellItemSelected = view->scene->cellItemSelected;
    view->fitInView(view->scene->cellItemSelected->image,Qt::KeepAspectRatio);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


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

// Resize window event CallBack
void MainWindow::resizeEvent(QResizeEvent*)
{
    view->resize(ui->centralWidget->frameSize().width()*3/4,ui->centralWidget->frameSize().height());

    if(!view->isHidden()){
        if(view->QGraphicsView::scene() == view->scene){
            view->adjustCellItems();
            sortWidget->show();
        }else if(view->QGraphicsView::scene() == view->sceneProcessing){
            view->fitInView(view->sceneProcessing->cellItemSelected->image,Qt::KeepAspectRatio);
            confWidget->show();
        }
    }
    ui->frame->setGeometry(ui->centralWidget->frameGeometry().center().x()-ui->frame->width()/2,
                       ui->centralWidget->frameGeometry().center().y()-ui->frame->height()/2,
                       ui->frame->width(),
                       ui->frame->height());

    sortWidget->resize(ui->centralWidget->frameSize().width()*1/4,ui->centralWidget->frameSize().height());
    sortWidget->setGeometry(ui->centralWidget->frameSize().width() * 3/4, 0, sortWidget->size().width(), sortWidget->size().height());

    confWidget->resize(ui->centralWidget->frameSize().width()*1/4,ui->centralWidget->frameSize().height());
    confWidget->setGeometry(ui->centralWidget->frameSize().width() * 3/4,0,confWidget->size().width(), confWidget->size().height());

}

// logout menu action callback
void MainWindow::logOut()
{
    currentUser = 0;
    view->hide();
    confWidget->hide();
    sortWidget->hide();
    ui->connectionWidget->show();
}

// About menu action callback
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

// AboutQt menu action callback
void MainWindow::aboutQt()
{
    QMessageBox::aboutQt(this, "About Qt");
}
