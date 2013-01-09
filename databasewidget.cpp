#include "databasewidget.h"

/// Database constructor
DatabaseWidget::DatabaseWidget(DataBase *database,QWidget *parent)
    : QWidget(parent),
      database(database),
      imageDbModified(false),
      userDbModified(false)
{
    Users *user = 0;
    CellItem *image = 0;
    QModelIndex index;
    int userNumLines = database->getUserNumlines();
    int imageNumLines = database->getImageNumlines();

    frame = new QFrame(this);
    layout = new QHBoxLayout(frame);
    saveButton = new QPushButton("Save",frame);
    cancelButton = new QPushButton("Cancel",frame);
    leftSpacer = new QSpacerItem(50,20,QSizePolicy::Expanding);
    rightSpacer = new QSpacerItem(50,20,QSizePolicy::Expanding);

    layout->addSpacerItem(leftSpacer);
    layout->addWidget(saveButton);
    layout->addWidget(cancelButton);
    layout->addSpacerItem(rightSpacer);

    frame->setGeometry(1250*3/4,750*1/2,1250*1/4,200);

    userDelegate = new ComboBoxDelegate("Permission",this);
    imageSizeDelegate = new ComboBoxDelegate("Size",this);
    imageCfdyDelegate = new ComboBoxDelegate("Confidentiality",this);

    userModel = new QStandardItemModel(userNumLines,4,this);
    imageModel = new QStandardItemModel(imageNumLines,7,this);

    userModel->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    userModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Username"));
    userModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Password"));
    userModel->setHeaderData(3, Qt::Horizontal, QObject::tr("Permission"));

    imageModel->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    imageModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
    imageModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Path"));
    imageModel->setHeaderData(3, Qt::Horizontal, QObject::tr("Type"));
    imageModel->setHeaderData(4, Qt::Horizontal, QObject::tr("Price"));
    imageModel->setHeaderData(5, Qt::Horizontal, QObject::tr("Confidentiality"));
    imageModel->setHeaderData(6, Qt::Horizontal, QObject::tr("Size"));    

    userTableView = new QTableView(this);
    userTableView->setModel(userModel);
    userTableView->setSortingEnabled(true);
    userTableView->setItemDelegateForColumn(3, userDelegate);

    for ( int i = 0; i < userModel->rowCount(); ++i )
    {
        userTableView->openPersistentEditor( userModel->index(i, 3));
    }

    imageTableView = new QTableView(this);
    imageTableView->setModel(imageModel);
    imageTableView->setSortingEnabled(true);
    imageTableView->setItemDelegateForColumn(5, imageCfdyDelegate);
    imageTableView->setItemDelegateForColumn(6, imageSizeDelegate);

    for ( int i = 0; i < imageModel->rowCount(); ++i )
    {
        imageTableView->openPersistentEditor(imageModel->index(i, 5));
        imageTableView->openPersistentEditor(imageModel->index(i, 6));
    }

    for(int i=0; i<userNumLines; i++){
        user = database->getUserDb(i);
        index = userModel->index(i,0);
        userModel->setData(index,user->getUserId());
        index = userModel->index(i,1);
        userModel->setData(index,user->getUsername());
        index = userModel->index(i,2);
        userModel->setData(index,user->getPassword());
        index = userModel->index(i,3);
        userModel->setData(index,QVariant((int)user->getPermission()));
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
        imageModel->setData(index,QVariant((int)image->getImageCfdy()));
        index = imageModel->index(i,6);
        imageModel->setData(index,QVariant((int)image->getImageSize()));
    }

    userTableView->hide();
    imageTableView->hide();

    QObject::connect(cancelButton, SIGNAL(clicked()), this, SLOT(onCancelButtonClicked()));
    QObject::connect(saveButton, SIGNAL(clicked()), this, SLOT(onSaveButtonClicked()));
    QObject::connect(userModel, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(onUserDbChanged()));
    QObject::connect(imageModel, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(onImageDbChanged()));

}

DatabaseWidget::~DatabaseWidget()
{
}

/// Resize event callback
void DatabaseWidget::resizeEvent(QResizeEvent *)
{
    userTableView->setGeometry(0,0,this->frameSize().width()*3/4,this->frameSize().height());
    imageTableView->setGeometry(0,0,this->frameSize().width()*3/4,this->frameSize().height());
    frame->setGeometry(this->frameSize().width()*3/4,750*1/2,this->frameSize().width()*1/4,200);
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
            userModel->setData(index,QVariant((int)user->getPermission()));
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
            imageModel->setData(index,QVariant((int)image->getImageCfdy()));
            index = imageModel->index(i,6);
            imageModel->setData(index,QVariant((int)image->getImageSize()));
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
            int permission = userModel->data(index).toInt();

            Users user(username,password,(Users::USER_PERMISSION) permission,id);

            database->addUserDb(&user);
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
            int confidentiality = imageModel->data(index).toInt();
            index = imageModel->index(i,6);
            int size = imageModel->data(index).toInt();

            CellItem cellItem;
            cellItem.setImageId(id);
            cellItem.setImageName(filename);
            cellItem.setImagePath(path);
            cellItem.setImageType(type);
            cellItem.setImagePrice(price);
            cellItem.setImageCfdy((CellItem::IMAGE_CONFIDENTIALITY) confidentiality);
            cellItem.setImageSize((CellItem::IMAGE_SIZE) size);

            database->addImageDb(&cellItem);
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

void DatabaseWidget::showUserDb()
{
    this->show();
    imageTableView->hide();
    userTableView->show();
}

void DatabaseWidget::showImageDb()
{
    this->show();
    userTableView->hide();
    imageTableView->show();
}
