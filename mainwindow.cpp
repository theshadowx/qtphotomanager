#include "mainwindow.h"
#include "cellitem.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    Users* adminUser = new Users("admin","root",Users::LEVEL_1,0);
    userChain = new UsersChain();
    userChain->addUser(adminUser);
    currentUser = 0;

    /***************** init interface *******************/

    ui->setupUi(this);

    menuBar     = new QMenuBar(this);
    quitAct     = new QAction(tr("&Quit"), this);
    aboutAct    = new QAction(tr("A&bout"), this);
    aboutQtAct  = new QAction(tr("Abo&ut Qt"), this);

    aboutAct->setShortcut(tr("Ctrl+B"));
    aboutQtAct->setShortcut(tr("Ctrl+U"));
    quitAct->setShortcut(tr("Ctrl+Q"));


    fileMenu = menuBar->addMenu(tr("&File"));
    fileMenu->addAction(quitAct);

    editMenu = menuBar->addMenu(tr("&Edit"));

    helpMenu = menuBar->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);


    ui->centralWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    this->setCentralWidget(ui->centralWidget);
    view = new graphicsView(ui->centralWidget);
    view->setGeometry(0,0,1250*3/4,750);
    view->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->installEventFilter(this);
    view->hide();

    sortWidget = new SortWidget(ui->centralWidget);
    sortWidget->setGeometry(1250*3/4,0,1250*1/4,750);
    sortWidget->hide();

    confWidget = new ConfWidget(ui->centralWidget);
    confWidget->setGeometry(1250*3/4,0,1250*1/4,750);
    confWidget->view = view;
    confWidget->hide();

/*
    dirPath = QDir(QDir::homePath() + "/.photoManager");
    if(!dirPath.exists())
        QDir().mkdir(dirPath.path());
*/
    this->setMenuBar(menuBar);


    /***************** connection SLOT/SIGNAL *******************/

    QObject::connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
    QObject::connect(aboutQtAct, SIGNAL(triggered()), this, SLOT(aboutQt()));
    QObject::connect(quitAct, SIGNAL(triggered()), this, SLOT(close()));
    QObject::connect(confWidget, SIGNAL(cancelButton_clicked()), sortWidget, SLOT(show()));
    QObject::connect(confWidget, SIGNAL(saveButton_clicked()), sortWidget, SLOT(show()));
    QObject::connect(view, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(showContextMenu(const QPoint&)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

// log in click
void MainWindow::on_pushButton_clicked()
{
    QString username = ui->userNameEdit->text();
    QString password = ui->passwordEdit->text();

    currentUser = userChain->getUser(username,password);
    if(currentUser){
        ui->connectionWidget->hide();
        view->show();
        sortWidget->show();
    }else{

    }

}

// submit click
void MainWindow::on_submitBut_clicked(){
    QString username = ui->usrCnEdit->text();
    QString password = ui->pwCnEdit->text();
    QString passwordconf = ui->pwCfCnEdit->text();

    QMessageBox msgBox;
    msgBox.setStandardButtons(QMessageBox::Ok);

    if(password != passwordconf){
        msgBox.setText("The passwords are not the same, please retry.");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        return;
    }else if(userChain->containsUser(username)){
        msgBox.setText("This username is not available, please retry.");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        return;
    }else{
        Users *user = new Users(username,password,Users::LEVEL_2);
        userChain->addUser(user);
        currentUser = user;
        view->show();
        sortWidget->show();
        ui->connectionWidget->hide();
        msgBox.setText("User added");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.exec();
    }
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*> (event);
        if(view->QGraphicsView::scene() == view->scene){
            if(mouseEvent->button() == Qt::LeftButton){
                CellItem *item = static_cast<CellItem*> (view->scene->itemAt(view->mapToScene(mouseEvent->pos())));
                if(item!=NULL){
                    if(view->scene->cellItemList.contains(item)){
                        onCellItemclicked(item);
                    }else{
                        CellItem *itemParent = static_cast<CellItem*> (item->parentItem());
                        onCellItemclicked(itemParent);
                    }
                }
            }
        }
    }
    return QMainWindow::eventFilter(obj, event);
}

void MainWindow::showContextMenu(const QPoint &pos)
{
    // for most widgets
    QPoint globalPos = view->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu optionMenu(this);
    QAction processImageAction("Traiter l'image",&optionMenu);
    QAction deleteImageAction("supprimer l'image",&optionMenu);
    QAction insertImageAction("inserer une image",&optionMenu);

    if(view->QGraphicsView::scene()==view->scene){
       if(view->scene->itemAt(view->mapToScene(pos))!=NULL){
            optionMenu.addAction(&processImageAction);
            optionMenu.addAction(&deleteImageAction);
            optionMenu.addAction(&insertImageAction);
       }else{
            optionMenu.addAction(&insertImageAction);
       }

        QAction* selectedItem = optionMenu.exec(globalPos);
        if(selectedItem == &processImageAction){
            CellItem *item = static_cast<CellItem*> (view->scene->itemAt(view->mapToScene(pos)));
            if(item!=NULL){
                if(view->scene->cellItemList.contains(item)){
                    onCellItemclicked(item);
                }else{
                    CellItem *itemParent = static_cast<CellItem*> (item->parentItem());
                    onCellItemclicked(itemParent);
                }
            }
        }else if(selectedItem == &processImageAction){

        }else if(selectedItem == &processImageAction){

        }
    }
}

void MainWindow::onCellItemclicked(CellItem *item)
{
    view->scene->cellItemSelected  = item;
    view->resize(view->parentWidget()->size().width()*3/4,view->parentWidget()->size().height());
    view->setScene(view->sceneProcessing);
    view->scene->removeItem(view->scene->cellItemSelected);
    view->sceneProcessing->addItem(view->scene->cellItemSelected->image);
    view->sceneProcessing->cellItemSelected = view->scene->cellItemSelected;

    sortWidget->hide();

    confWidget->resize(confWidget->parentWidget()->frameSize().width()*1/4,confWidget->parentWidget()->frameSize().height());
    confWidget->setGeometry(confWidget->parentWidget()->frameSize().width() * 3/4,0,confWidget->size().width(),confWidget->size().height());
    confWidget->show();
    #ifdef Q_OS_LINUX
        QString strPath = QDir().currentPath() + "/../../PhotoManager/" + item->getImagePath();
        confWidget->matOriginal = cv::imread(strPath.toStdString());
        confWidget->matProcessed = cv::imread(strPath.toStdString());
    #endif
    confWidget->pixOriginal = item->image->pixmap();
    view->fitInView(view->scene->cellItemSelected->image,Qt::KeepAspectRatio);

}

// fonction appliquée lors de changement de taille de la fenêtre
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
    }else{
        ui->frame->setGeometry(ui->centralWidget->frameGeometry().center().x()-ui->frame->width()/2,
                               ui->centralWidget->frameGeometry().center().y()-ui->frame->height()/2,
                               ui->frame->width(),
                               ui->frame->height());
    }

    sortWidget->resize(ui->centralWidget->frameSize().width()*1/4,ui->centralWidget->frameSize().height());
    sortWidget->setGeometry(ui->centralWidget->frameSize().width() * 3/4, 0, sortWidget->size().width(), sortWidget->size().height());

    confWidget->resize(ui->centralWidget->frameSize().width()*1/4,ui->centralWidget->frameSize().height());
    confWidget->setGeometry(ui->centralWidget->frameSize().width() * 3/4,0,confWidget->size().width(), confWidget->size().height());

}

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

void MainWindow::aboutQt()
{
    QMessageBox::aboutQt(this, "About Qt");
}



