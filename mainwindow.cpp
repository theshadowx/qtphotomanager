#include "mainwindow.h"
#include "cellitem.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(const QString &usersTable, const QString &imagesTable, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    /***************** Base de Données *******************/

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(":memory:");
    db.open();

    query = new QSqlQuery(db);

    // create users table
    query->exec("create table users (id int primary key, "
               "username varchar(20), password varchar(20),permission int)");

    query->exec("insert into users values(1, 'admin', 'root', 1)");

    // create image table
    query->exec("create table images (id int primary key,"
               "imagefile int,"
               "filename varchar(20),"
               "filepath varchar(20),"
               "resolution varchar(20),"
               "price int,"
                "size int,"
                "levelConf varchar(1))");

    query->exec("insert into images values(1,1,'image_1','images/image_1.jpg','1440x900','500','252','F')");
    query->exec("insert into images values(2,2,'image_2','images/image_2.jpg','1440x900','600','266','F')");
    query->exec("insert into images values(3,3,'image_3','images/image_3.jpg','1920x1080','700','359','F')");
    query->exec("insert into images values(4,4,'image_4','images/image_4.jpg','1600x1200','800','217','F')");
    query->exec("insert into images values(5,5,'image_5','images/image_5.jpg','1440x900','900','142','F')");
    query->exec("insert into images values(6,6,'image_6','images/image_6.jpg','1280x1024','1000','538','F')");
    query->exec("insert into images values(7,7,'image_7','images/image_7.jpg','1440x900','1100','87','F')");

    userTable = new QSqlTableModel(this);
    userTable->setTable(usersTable);
    userTable->setEditStrategy(QSqlTableModel::OnManualSubmit);!
    userTable->select();

    imageTable = new QSqlTableModel(this);
    imageTable->setTable(imagesTable);
    imageTable->setEditStrategy(QSqlTableModel::OnManualSubmit);
    imageTable->select();

   /***************** init interface *******************/

    this->setWindowTitle("Photo Manager");
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
    view->setGeometry(0,0,1250,750);
    view->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->hide();


    confWidget = new ConfWidget(ui->centralWidget);
    confWidget->setGeometry(1250*3/4,0,1250*1/4,750);
    confWidget->hide();

    dirPath = QDir(QDir::homePath() + "/.photoManager");
    if(!dirPath.exists())
        QDir().mkdir(dirPath.path());

    this->setMenuBar(menuBar);


    /***************** connection SLOT/SIGNAL *******************/

    QObject::connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
    QObject::connect(aboutQtAct, SIGNAL(triggered()), this, SLOT(aboutQt()));
    QObject::connect(quitAct, SIGNAL(triggered()), this, SLOT(close()));
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

    int userCount = userTable->rowCount();
    int imageCount = imageTable->rowCount();

    int imageOffsetHeight = 150;
    int imageOffsetWidth = 170;
    int leftMargin = 70;
    int topMargin = 40;
    int bottomMargin = 40;
    int columnCount =(int) (ui->centralWidget->frameSize().width()-leftMargin)/(imageOffsetWidth+leftMargin)+1;

    // verifier si le nom d'utilisateur et le mots de passe existent dèja dans la base de donnée
    // si oui, cacher le widget de connection et afficher view
    for (int i = 0; i < userCount; i++) {
        QSqlRecord recordUsers = userTable->record(i);
        if(username == recordUsers.value("username").toString() && password == recordUsers.value("password").toString()){
            ui->connectionWidget->hide();
            view->show();
            break;
        }
    }

    // si view n'est plus caché (nom d'utilisateur et mot de passe sont correctes )
    // Affichage des images
    // ajout des images dans une liste
    if(!view->isHidden()){
        confWidget->view = view;
        view->confWidget = confWidget;
        for (int i = 0; i < imageCount; i++) {
            CellItem *cell;
            QSqlRecord recordImage = imageTable->record(i);
            int id = recordImage.value("id").toInt();
            QString fileName = recordImage.value("filename").toString();
            QString filePath = recordImage.value("filepath").toString();
            int price = recordImage.value("price").toInt();

            int columnOffset = (37 * (i%columnCount));
            int x = ((i % columnCount) * imageOffsetWidth) + leftMargin + columnOffset;
            int y = ((i / columnCount) * (imageOffsetHeight + bottomMargin))+ topMargin;

            cell = new CellItem(id,fileName,filePath,price,QPixmap(":/" + filePath),0);
            cell->image->setData(0, i);
            cell->setPos(view->mapToScene(x, y));
            view->scene->addItem(cell);
            view->scene->cellItemList.append(cell);
        }
    }
}

// submit click
void MainWindow::on_submitBut_clicked(){

    QString username = ui->usrCnEdit->text();
    QString password = ui->pwCnEdit->text();
    QString passwordcnf = ui->pwCfCnEdit->text();

    if(password != passwordcnf){
        return;
    }else{
        QString strSQL("insert into users values(2,'"+ username + "','"+ password +"', 1)");
        qDebug() << strSQL;
        bool ok = query->exec(strSQL);
        qDebug() << ok;
    }
}

// fonction appliquée lors de changement de taille de la fenêtre
void MainWindow::resizeEvent(QResizeEvent*)
{
    if(!view->isHidden()){
        if(view->QGraphicsView::scene()==view->scene){

            view->resize(ui->centralWidget->frameSize());
            view->adjustCellItems();

        }else if(view->QGraphicsView::scene()==view->sceneProcessing){

            view->resize(ui->centralWidget->frameSize().width()*3/4,ui->centralWidget->frameSize().height());
            view->fitInView(view->sceneProcessing->cellItemSelected->image,Qt::KeepAspectRatio);

            confWidget->resize(ui->centralWidget->frameSize().width()*1/4,ui->centralWidget->frameSize().height());
            confWidget->setGeometry(ui->centralWidget->frameSize().width() * 3/4,0,confWidget->size().width(),confWidget->size().height());
            confWidget->show();

        }else{
            view->resize(ui->centralWidget->frameSize());
        }

    }else{

    }
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


