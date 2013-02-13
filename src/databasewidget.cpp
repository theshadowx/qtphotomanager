#include "databasewidget.h"
#include "math.h"

/// Database constructor
DatabaseWidget::DatabaseWidget(DataBase *database,QWidget *parent)
    : QWidget(parent), database(database), imageDbModified(false),
      userDbModified(false), jpg(0),bmp(0),png(0),small(0),medium(0),
      large(0), Rs(0), Fs(0), low(0), average(0), high(0), total(0)
{
    Users *user = 0;
    CellItem *image = 0;
    QModelIndex index;
    int userNumLines = database->getUserNumlines();
    int imageNumLines = database->getImageNumlines();

    /** *************** init interface ***************** **/

    saveCancelFrame = new QFrame(this);
    saveCancellayout = new QHBoxLayout(saveCancelFrame);
    saveButton = new QPushButton("Save",saveCancelFrame);
    cancelButton = new QPushButton("Cancel",saveCancelFrame);
    leftSpacer = new QSpacerItem(50,20,QSizePolicy::Expanding);
    rightSpacer = new QSpacerItem(50,20,QSizePolicy::Expanding);

    saveCancellayout->addSpacerItem(leftSpacer);
    saveCancellayout->addWidget(saveButton);
    saveCancellayout->addWidget(cancelButton);
    saveCancellayout->addSpacerItem(rightSpacer);

    titleLabel = new QLabel(this);
    titleLabel->setFont(QFont(QFont().defaultFamily(),20,QFont::Bold));

    userDelegate = new ComboBoxDelegate("Permission",this);
    imageSizeDelegate = new ComboBoxDelegate("Size",this);
    imageCfdyDelegate = new ComboBoxDelegate("Confidentiality",this);

    /** *************** UserDB Frame ***************** **/

    imageDbFrame = new QFrame(this);
    imageDbFrame->hide();

    /** *************** pie parameter selector ***************** **/

    pieParamSelector = new QComboBox(imageDbFrame);
    QStringList parameterList;
    parameterList << "Size" <<"Type" << "Price" << "Confidentiality";
    pieParamSelector->addItems(parameterList);

    /** *************** pie construction ***************** **/

    pieChartItem = new PieChart;
    pieChartItem->hide();

    pieChartView = new QGraphicsView(imageDbFrame);
    QGraphicsScene *scenePieChart = new QGraphicsScene(pieChartView);
    pieChartView->setObjectName("viewPieChart");
    pieChartView->setFrameShape(QFrame::NoFrame);
    pieChartView->setScene(scenePieChart);
    pieChartView->scene()->addItem(pieChartItem);

    legendLine1 = new QLabel(imageDbFrame);
    legendLine2 = new QLabel(imageDbFrame);
    legendLine3 = new QLabel(imageDbFrame);

    legendLine1->setStyleSheet("QLabel{color : #a02503; }");
    legendLine2->setStyleSheet("QLabel{color : #881469; }");
    legendLine3->setStyleSheet("QLabel{color : #414684; }");

    legendLine1->setFont(QFont(QFont().defaultFamily(),9,QFont::Bold));
    legendLine2->setFont(QFont(QFont().defaultFamily(),9,QFont::Bold));
    legendLine3->setFont(QFont(QFont().defaultFamily(),9,QFont::Bold));

    legendLine1->setMaximumHeight(28);
    legendLine2->setMaximumHeight(28);
    legendLine3->setMaximumHeight(28);

    legendLine1->hide();
    legendLine2->hide();
    legendLine3->hide();

    /** *************** ImageView ***************** **/

    QGraphicsScene *imageScene = new QGraphicsScene(this);
    imageView = new QGraphicsView(imageDbFrame);
    imageView->setObjectName("imageView");
    imageView->setStyleSheet("QGraphicsView{background-color: transparent}");
    imageView->setFrameShape(QFrame::NoFrame);
    imageView->setScene(imageScene);

    imageItem = new ImageItem();
    imageScene->addItem(imageItem);

    /** *************** setup models ***************** **/

    userModel = new QStandardItemModel(userNumLines,5,this);
    imageModel = new QStandardItemModel(imageNumLines,7,this);

    userModel->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    userModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Username"));
    userModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Password"));
    userModel->setHeaderData(3, Qt::Horizontal, QObject::tr("Permission"));
    userModel->setHeaderData(4, Qt::Horizontal, QObject::tr("Email"));

    imageModel->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    imageModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
    imageModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Path"));
    imageModel->setHeaderData(3, Qt::Horizontal, QObject::tr("Type"));
    imageModel->setHeaderData(4, Qt::Horizontal, QObject::tr("Price"));
    imageModel->setHeaderData(5, Qt::Horizontal, QObject::tr("Confidentiality"));
    imageModel->setHeaderData(6, Qt::Horizontal, QObject::tr("Size"));

    /** *************** user table veiw ***************** **/

    userTableView = new QTableView(this);
    userTableView->setModel(userModel);
    userTableView->setSortingEnabled(true);
    userTableView->hide();
    userTableView->setItemDelegateForColumn(3, userDelegate);

    /** *************** image table veiw ***************** **/

    imageTableView = new QTableView(this);
    imageTableView->setModel(imageModel);
    imageTableView->setSortingEnabled(true);
    imageTableView->hide();
    imageTableView->setItemDelegateForColumn(5, imageCfdyDelegate);
    imageTableView->setItemDelegateForColumn(6, imageSizeDelegate);

    /** *************** filling models and counting for stats ***************** **/

    for(int i=0; i<userNumLines; i++){
        user = database->getUserDb(i);
        index = userModel->index(i,0);
        userModel->setData(index,user->getUserId());
        index = userModel->index(i,1);
        userModel->setData(index,user->getUsername());
        index = userModel->index(i,2);
        userModel->setData(index,user->getPassword());
        index = userModel->index(i,3);
        userModel->setData(index,QVariant(user->enumPermissionToQString()));
        index = userModel->index(i,4);
        userModel->setData(index,user->getEmail());
        delete user;
        user = 0;
    }

    for(int i=0; i<imageNumLines; i++){
        image = database->getImageDb(i);
        index = imageModel->index(i,0);
        imageModel->setData(index,image->getImageId());
        index = imageModel->index(i,1);
        imageModel->setData(index,image->getImageName());
        index = imageModel->index(i,2);
        imageModel->setData(index,image->getImagePath());
        index = imageModel->index(i,3);
        imageModel->setData(index,image->getImageType());
        index = imageModel->index(i,4);
        imageModel->setData(index,image->getImagePrice());
        index = imageModel->index(i,5);
        imageModel->setData(index,QVariant(image->enumCfdyToQString()));
        index = imageModel->index(i,6);
        imageModel->setData(index,QVariant(image->enumSizeToQString()));

        if (image->getImageType()=="jpg") {jpg++;}
        else if (image->getImageType()=="png") {png++;}
        else if (image->getImageType()=="bmp") {bmp++;}

        if (image->getImageSize()==CellItem::SMALL) {small++;}
        else if (image->getImageSize()==CellItem::MEDIUM) {medium++;}
        else if (image->getImageSize()==CellItem::LARGE) {large++;}

        if (image->getImagePrice()<=500) {low++;}
        else if (image->getImagePrice()>500 && image->getImagePrice()<=1000) {average++;}
        else if (image->getImagePrice()>1000) {high++;}

        if (image->getImageCfdy()==CellItem::R) {Rs++;}
        else if (image->getImageCfdy()==CellItem::F) {Fs++;}

        delete image;
        image = 0;
    }
    total = imageNumLines;

    /** *************** Connection SLOT/SIGNAL ***************** **/

    QObject::connect(cancelButton, SIGNAL(clicked()), this, SLOT(onCancelButtonClicked()));
    QObject::connect(saveButton, SIGNAL(clicked()), this, SLOT(onSaveButtonClicked()));
    QObject::connect(userModel, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(onUserDbChanged()));
    QObject::connect(imageModel, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(onImageDbChanged()));
    QObject::connect(imageTableView, SIGNAL(clicked(QModelIndex)), this, SLOT(updateImageView(QModelIndex)));
    QObject::connect(imageModel, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(updateChart()));
    QObject::connect(pieParamSelector,SIGNAL(activated(QString)),this,SLOT(updateChart()));
    QObject::connect(this, SIGNAL(chartUpdated(QString)), this, SLOT(drawChart(QString)));
    QObject::connect(this, SIGNAL(cancelButtonClicked()), imageDbFrame, SLOT(hide()));
    QObject::connect(this, SIGNAL(saveButtonClicked()), imageDbFrame, SLOT(hide()));
}

DatabaseWidget::~DatabaseWidget()
{
}

/// Draw chart
void DatabaseWidget::drawChart(QString param)
{
    QString str;
    float percentage;
    /// Type
    if (param == "Type"){
        pieChartItem->buildAChart(param, total, jpg, bmp, png);
        percentage = round(100*(float)jpg/(float)total);
        str.append(QString("%1").arg(percentage));
        legendLine1->setText("JPEG : "+str+"%");
        str.clear();
        percentage = round(100*(float)bmp/(float)total);
        str.append(QString("%1").arg(percentage));
        legendLine2->setText("BMP : "+str+"%");
        str.clear();
        percentage = round(100*(float)png/(float)total);
        str.append(QString("%1").arg(percentage));
        legendLine3->setText("PNG : "+str+"%");
        str.clear();
    /// Size
    }else if (param == "Size"){
        pieChartItem->buildAChart(param, total, small, medium, large);
        percentage = round(100*(float)small/(float)total);
        str.append(QString("%1").arg(percentage));
        legendLine1->setText("Small : "+str+"%");
        str.clear();
        percentage = round(100*(float)medium/(float)total);
        str.append(QString("%1").arg(percentage));
        legendLine2->setText("Medium : "+str+"%");
        str.clear();
        percentage = round(100*(float)large/(float)total);
        str.append(QString("%1").arg(percentage));
        legendLine3->setText("Large : "+str+"%");
        str.clear();
    /// Price
    }else if (param == "Price"){
        pieChartItem->buildAChart(param, total, low, average, high);
        percentage = round(100*(float)low/(float)total);
        str.append(QString("%1").arg(percentage));
        legendLine1->setText("Low price : "+str+"%");
        str.clear();
        percentage = round(100*(float)average/(float)total);
        str.append(QString("%1").arg(percentage));
        legendLine2->setText("Average price : "+str+"%");
        str.clear();
        percentage = round(100*(float)high/(float)total);
        str.append(QString("%1").arg(percentage));
        legendLine3->setText("High price : "+str+"%");
        str.clear();
    /// Confidentiality
    }else if (param == "Confidentiality"){
        pieChartItem->buildAChart(param, total, Rs, Fs, 0);
        percentage = round(100*(float)Rs/(float)total);
        str.append(QString("%1").arg(percentage));
        legendLine1->setText("Reserved: "+str+"%");
        str.clear();
        percentage = round(100*(float)Fs/(float)total);
        str.append(QString("%1").arg(percentage));
        legendLine2->setText("Free : "+str+"%");
        str.clear();
        legendLine3->setText(" ");
    }
    if(pieParamSelector->currentText() == "Choose a chart parameter"){
        pieChartItem->hide();
        legendLine1->hide();
        legendLine2->hide();
        legendLine3->hide();
    }else if(pieParamSelector->currentText() == "Confidentiality"){
        pieChartItem->show();
        legendLine1->show();
        legendLine2->show();
        legendLine3->hide();
    }else{
        pieChartItem->show();
        legendLine1->show();
        legendLine2->show();
        legendLine3->show();
    }
    pieChartView->scene()->update();
}

void DatabaseWidget::updateChart()
{
    QModelIndex index;
    int imageNumLines = database->getImageNumlines();

    jpg = 0;
    bmp = 0;
    png = 0;
    small = 0;
    medium = 0;
    large = 0;
    Rs = 0;
    Fs = 0;
    low = 0;
    average = 0;
    high = 0;

    for(int i=0; i<imageNumLines; i++){
        index = imageModel->index(i,3);
        QString type = imageModel->data(index).toByteArray();
        index = imageModel->index(i,4);
        int price = imageModel->data(index).toInt();
        index = imageModel->index(i,5);
        QString confidentiality = imageModel->data(index).toByteArray();
        index = imageModel->index(i,6);
        QString size = imageModel->data(index).toByteArray();

        if (type == "jpg") {jpg++;}
        else if (type == "png") {png++;}
        else if (type == "bmp") {bmp++;}

        if (CellItem().qstringToEnumSize(size) == CellItem::SMALL) {small++;}
        else if (CellItem().qstringToEnumSize(size) == CellItem::MEDIUM) {medium++;}
        else if (CellItem().qstringToEnumSize(size) == CellItem::LARGE) {large++;}

        if (price<=500){low++;}
        else if (price>500 && price<=1000) {average++;}
        else if (price>1000) {high++;}

        if (CellItem().qstringToEnumCfdy(confidentiality) == CellItem::R) {Rs++;}
        else if (CellItem().qstringToEnumCfdy(confidentiality) == CellItem::F) {Fs++;}
    }
    total = imageNumLines;
    if(imageNumLines!=0)
        emit chartUpdated(pieParamSelector->currentText());
}

void DatabaseWidget::updateImageView(QModelIndex index)
{
    int row = index.row();
    index = imageModel->index(row,1);
    QString fileName = imageModel->data(index).toByteArray();
    index = imageModel->index(row,2);
    QString path = imageModel->data(index).toByteArray();
    index = imageModel->index(row,3);
    QString type = imageModel->data(index).toByteArray();

    QString filePath = path + QDir().separator() + fileName + "." + type;
    imageItem->setPixmap(filePath);
    imageView->setSceneRect(imageView->geometry());
    imageItem->setPos(imageView->mapToScene(0,0).x(),imageView->mapToScene(0,0).y());
    float scaleFactor = (float) (imageView->size().width()) / imageItem->boundingRect().width();
    imageItem->adjust(imageView->size().width(),scaleFactor*imageItem->pixmap().height());
}

/// Resize event callback
void DatabaseWidget::resizeEvent(QResizeEvent *)
{
    titleLabel->setGeometry(this->frameSize().width()*3/4 + 20, 0, this->frameSize().width()*1/4-20, 100);

    userTableView->setGeometry(0,0,this->frameSize().width()*3/4,this->frameSize().height());
    imageTableView->setGeometry(0,0,this->frameSize().width()*3/4,this->frameSize().height());
    saveCancelFrame->setGeometry(this->frameSize().width()*3/4, this->frameSize().height()-50, this->frameSize().width()*1/4, 50);

    imageDbFrame->setGeometry(this->frameSize().width()*3/4,80, this->frameSize().width()*1/4,this->frameSize().height()-150);

    pieParamSelector->setGeometry(20, 0, imageDbFrame->size().width()-40, 30);

    pieChartView->setGeometry(20,  pieParamSelector->pos().y() + pieParamSelector->size().height()+10, imageDbFrame->size().width()/2,imageDbFrame->size().width()/2);
    pieChartView->setSceneRect(pieChartView->geometry());
    pieChartItem->setSize(QSize(imageDbFrame->size().width()*1/2-10,imageDbFrame->size().width()*1/2-10));
    pieChartItem->setPos(pieChartView->mapToScene(0,0).x(),pieChartView->mapToScene(0,0).y());

    legendLine1->setGeometry(pieChartView->pos().x()+pieChartView->size().width()+10, pieChartView->pos().y() + 30,this->frameSize().width()*1/8-40 , 28);
    legendLine2->setGeometry(pieChartView->pos().x()+pieChartView->size().width()+10, pieChartView->pos().y() + 60,this->frameSize().width()*1/8-40 , 28);
    legendLine3->setGeometry(pieChartView->pos().x()+pieChartView->size().width()+10, pieChartView->pos().y() + 90,this->frameSize().width()*1/8-40 , 28);

    imageView->setGeometry(20,pieChartView->pos().y()+pieChartView->size().height()+10,imageDbFrame->size().width()-40,(imageDbFrame->size().width()-40)*3/4);
    imageView->setSceneRect(imageView->geometry());
    imageItem->setPos(imageView->mapToScene(0,0).x(),imageView->mapToScene(0,0).y());
    float scaleFactor = (float) (imageView->size().width()) / imageItem->boundingRect().width();
    imageItem->adjust(imageView->size().width(),scaleFactor*imageItem->pixmap().height());

}

/// Paint event callback
void DatabaseWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

/// Cancel button callback
void DatabaseWidget::onCancelButtonClicked()
{
    Users *user = 0;
    CellItem *image = 0;
    QModelIndex index;
    int userNumLines = database->getUserNumlines();
    int imageNumLines = database->getImageNumlines();

    if(userDbModified){
        userDbModified = false;
        for(int i=0; i<userNumLines; i++){
            user = database->getUserDb(i);
            index = userModel->index(i,0);
            userModel->setData(index,user->getUserId());
            index = userModel->index(i,1);
            userModel->setData(index,user->getUsername());
            index = userModel->index(i,2);
            userModel->setData(index,user->getPassword());
            index = userModel->index(i,3);
            userModel->setData(index,QVariant(user->enumPermissionToQString()));
            index = userModel->index(i,4);
            userModel->setData(index,user->getEmail());
            delete user;
            user = 0;
        }
    }

    if(imageDbModified){
        imageDbModified = false;
        for(int i=0; i<imageNumLines; i++){
            image = database->getImageDb(i);
            index = imageModel->index(i,0);
            imageModel->setData(index,image->getImageId());
            index = imageModel->index(i,1);
            imageModel->setData(index,image->getImageName());
            index = imageModel->index(i,2);
            imageModel->setData(index,image->getImagePath());
            index = imageModel->index(i,3);
            imageModel->setData(index,image->getImageType());
            index = imageModel->index(i,4);
            imageModel->setData(index,image->getImagePrice());
            index = imageModel->index(i,5);
            imageModel->setData(index,QVariant(image->enumCfdyToQString()));
            index = imageModel->index(i,6);
            imageModel->setData(index,QVariant(image->enumSizeToQString()));
            delete image;
            image = 0;
        }
    }

    this->hide();
    imageTableView->hide();
    userTableView->hide();
    emit cancelButtonClicked();
}

/// Save button callback
void DatabaseWidget::onSaveButtonClicked()
{
    QModelIndex index;
    int userNumLines = database->getUserNumlines();
    int imageNumLines = database->getImageNumlines();

    if(userDbModified){
        userDbModified = false;
        database->clearUserDb();

        for(int i=0; i<userNumLines; i++){
            index = userModel->index(i,0);
            int id = userModel->data(index).toInt();
            index = userModel->index(i,1);
            QString username = userModel->data(index).toByteArray();
            index = userModel->index(i,2);
            QString password = userModel->data(index).toByteArray();
            index = userModel->index(i,3);
            QString permission = userModel->data(index).toByteArray();
            index = userModel->index(i,4);
            QString email = userModel->data(index).toByteArray(); ;

            Users *user = new Users(username,password, Users().qstringToEnumPermission(permission),email,id);

            database->addUserDb(user);
            delete user;
        }
        emit userDbChanged(database);
    }

    if(imageDbModified){
        imageDbModified = false;
        database->clearImageDb();

        for(int i=0; i<imageNumLines; i++){
            index = imageModel->index(i,0);
            int id = imageModel->data(index).toInt();
            index = imageModel->index(i,1);
            QString filename = imageModel->data(index).toByteArray();
            index = imageModel->index(i,2);
            QString path = imageModel->data(index).toByteArray();
            index = imageModel->index(i,3);
            QString type = imageModel->data(index).toByteArray();
            index = imageModel->index(i,4);
            int price = imageModel->data(index).toInt();
            index = imageModel->index(i,5);
            QString confidentiality = imageModel->data(index).toByteArray();
            index = imageModel->index(i,6);
            QString size = imageModel->data(index).toByteArray();


            CellItem *cellItem = new CellItem();
            cellItem->setImageId(id);
            cellItem->setImageName(filename);
            cellItem->setImagePath(path);
            cellItem->setImageType(type);
            cellItem->setImagePrice(price);
            cellItem->qstringToEnumCfdy(confidentiality);

            cellItem->qstringToEnumSize(size);

            database->addImageDb(cellItem);
            delete cellItem;
        }
        emit imageDbChanged(database);
    }

    this->hide();
    imageTableView->hide();
    userTableView->hide();
    emit saveButtonClicked();
}

/// User database changed callback
void DatabaseWidget::onUserDbChanged()
{
    userDbModified = true;
}

/// Image database changed callback
void DatabaseWidget::onImageDbChanged()
{
    imageDbModified = true;
}

/// Delete a list of images from database
bool DatabaseWidget::onImageDeleted(QList<CellItem *> cellItemList)
{
    database->deleteImageDb(cellItemList);
    this->updateImageTable();
    return true;
}

/// Show user database
void DatabaseWidget::showUserDb()
{
    this->show();
    titleLabel->setText("User Database");
    imageTableView->hide();
    imageDbFrame->hide();
    userTableView->show();
}

/// Show image database
void DatabaseWidget::showImageDb()
{
    this->show();
    titleLabel->setText("Image Database");
    userTableView->hide();
    imageTableView->show();
    imageDbFrame->show();
}

/// Update the image table
void DatabaseWidget::updateImageTable()
{
    int imageNumLines = database->getImageNumlines();

    QModelIndex index;
    CellItem *image = 0;

    jpg=0; png=0; bmp=0;
    small=0; medium=0; large=0;
    Rs=0; Fs=0;
    low=0; average=0; high=0;

    imageModel->removeRows(0,imageModel->rowCount());
    imageModel->setRowCount(imageNumLines);

    for(int i=0; i<imageNumLines; i++){
        image = database->getImageDb(i);
        index = imageModel->index(i,0);
        imageModel->setData(index,image->getImageId());
        index = imageModel->index(i,1);
        imageModel->setData(index,image->getImageName());
        index = imageModel->index(i,2);
        imageModel->setData(index,image->getImagePath());
        index = imageModel->index(i,3);
        imageModel->setData(index,image->getImageType());
        index = imageModel->index(i,4);
        imageModel->setData(index,image->getImagePrice());
        index = imageModel->index(i,5);
        imageModel->setData(index,QVariant(image->enumCfdyToQString()));
        index = imageModel->index(i,6);
        imageModel->setData(index,QVariant(image->enumSizeToQString()));

        if (image->getImageType()=="jpg") {jpg++;}
        else if (image->getImageType()=="png") {png++;}
        else if (image->getImageType()=="bmp") {bmp++;}

        if (image->getImageSize()==CellItem::SMALL) {small++;}
        else if (image->getImageSize()==CellItem::MEDIUM) {medium++;}
        else if (image->getImageSize()==CellItem::LARGE) {large++;}

        if (image->getImagePrice()<=500) {low++;}
        else if (image->getImagePrice()>500 && image->getImagePrice()<=1000) {average++;}
        else if (image->getImagePrice()>1000) {high++;}

        if (image->getImageCfdy()==CellItem::R) {Rs++;}
        else if (image->getImageCfdy()==CellItem::F) {Fs++;}

        delete image;
        image = 0;
    }
    total=Rs+Fs;
}

/// Update the user table
void DatabaseWidget::updateUserTable()
{
    int userNumLines = database->getUserNumlines();

    QModelIndex index;
    Users *user = 0;

    userModel->removeRows(0,userNumLines);
    userModel->setRowCount(userNumLines);

    for(int i=0; i<userNumLines; i++){
        user = database->getUserDb(i);
        index = userModel->index(i,0);
        userModel->setData(index,user->getUserId());
        index = userModel->index(i,1);
        userModel->setData(index,user->getUsername());
        index = userModel->index(i,2);
        userModel->setData(index,user->getPassword());
        index = userModel->index(i,3);
        userModel->setData(index,QVariant((user->enumPermissionToQString())));
        index = userModel->index(i,4);
        userModel->setData(index,user->getEmail());
        delete user;
        user = 0;
    }
}
