#include "dialogproperties.h"

DialogProperties::DialogProperties(CellItem *cellItem, QWidget *parent)
    :QDialog(parent)
{
    this->setFixedSize(435,280);
    this->setWindowTitle("Image Properties");

    currentCellItem = cellItem;

    /********* Push Buttons *************/
    buttonBox = new QDialogButtonBox(this);

    previousImageButton = new QPushButton("Previous",buttonBox);
    nextImageButton = new QPushButton("Next",buttonBox);
    closeButton = new QPushButton("Close",buttonBox);

    previousImageButton->setGeometry(0,0,50,30);
    nextImageButton->setGeometry(0,0,50,30);
    closeButton->setGeometry(0,0,50,30);

    previousImageButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    nextImageButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    closeButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    buttonBox->addButton(closeButton,QDialogButtonBox::ApplyRole);
    buttonBox->addButton(nextImageButton,QDialogButtonBox::ApplyRole);
    buttonBox->addButton(previousImageButton,QDialogButtonBox::ApplyRole);
    buttonBox->setOrientation(Qt::Horizontal);

    buttonBox->setGeometry(0,240,400,35);

    /********* Tab Widget *************/
    tabWidget = new QTabWidget(this);
    tabWidget->setGeometry(10,10,415,220);

    pageGeneral = new QWidget(tabWidget);
    pageModification = new QWidget(tabWidget);

    tabWidget->addTab(pageGeneral,"General");
    tabWidget->addTab(pageModification,"Modification");

    /*********** Label ******************/
    nameLabel = new QLabel("Name :",pageGeneral);
    widthLabel = new QLabel("Width :",pageGeneral);
    heightLabel = new QLabel("Height :",pageGeneral);
    typeLabel = new QLabel("Type :",pageGeneral);
    sizeLabel = new QLabel("Size :",pageGeneral);
    weightLabel = new QLabel("Weight :",pageGeneral);
    priceLabel =  new QLabel("Price :",pageGeneral);
    cfdyLabel = new QLabel("Cfdy :",pageGeneral);
    pathLabel = new QLabel("Path :",pageGeneral);

    nameLabel->setGeometry(150,5,55,20);
    widthLabel->setGeometry(150,25,55,20);
    heightLabel->setGeometry(150,45,55,20);
    typeLabel->setGeometry(150,65,55,20);
    sizeLabel->setGeometry(150,85,55,20);
    weightLabel->setGeometry(150,105,55,20);
    priceLabel->setGeometry(150,125,55,20);
    cfdyLabel->setGeometry(150,145,55,20);
    pathLabel->setGeometry(150,165,55,20);

    nameLabel->setFont(QFont(QFont().defaultFamily(),10,QFont::Bold));
    widthLabel->setFont(QFont(QFont().defaultFamily(),10,QFont::Bold));
    heightLabel->setFont(QFont(QFont().defaultFamily(),10,QFont::Bold));
    typeLabel->setFont(QFont(QFont().defaultFamily(),10,QFont::Bold));
    sizeLabel->setFont(QFont(QFont().defaultFamily(),10,QFont::Bold));
    weightLabel->setFont(QFont(QFont().defaultFamily(),10,QFont::Bold));
    priceLabel->setFont(QFont(QFont().defaultFamily(),10,QFont::Bold));
    cfdyLabel->setFont(QFont(QFont().defaultFamily(),10,QFont::Bold));
    pathLabel->setFont(QFont(QFont().defaultFamily(),10,QFont::Bold));


    /*********** Data ******************/
    nameData = new QLabel(QString("%1").arg(currentCellItem->getImageName()),pageGeneral);
    widthData = new QLabel(QString("%1 pixels").arg(currentCellItem->image->pixmap().width()),pageGeneral);
    heightData = new QLabel(QString("%1 pixels").arg(currentCellItem->image->pixmap().height()),pageGeneral);
    typeData = new QLabel(QString("%1").arg(currentCellItem->getImageType()),pageGeneral);
    sizeData = new QLabel(currentCellItem->enumSizeToQString(),pageGeneral);
    weightData = new QLabel(QString("%1 Bytes").arg(QFile(QString("%1").arg(currentCellItem->getImagePath()+
                                                                            QDir().separator()+
                                                                            currentCellItem->getImageName()+
                                                                            "."+
                                                                            currentCellItem->getImageType())).size()),pageGeneral);
    priceData = new QLabel(QString("%1").arg(currentCellItem->getImagePrice()).append(QString::fromUtf8(" \u20AC")),pageGeneral);
    cfdyData = new QLabel(currentCellItem->enumCfdyToQString(),pageGeneral);
    pathData = new QLabel(QString("%1").arg(currentCellItem->getImagePath()),pageGeneral);

    nameData->setGeometry(210,5,225,20);
    widthData->setGeometry(210,25,225,20);
    heightData->setGeometry(210,45,225,20);
    typeData->setGeometry(210,65,225,20);
    sizeData->setGeometry(210,85,225,20);
    weightData->setGeometry(210,105,225,20);
    priceData->setGeometry(210,125,225,20);
    cfdyData->setGeometry(210,145,225,20);
    pathData->setGeometry(210,165,225,20);

    /********** Image ********************/

    QGraphicsScene *imageScene = new QGraphicsScene();

    imageView = new QGraphicsView(pageGeneral);
    imageView->setGeometry(15,20,120,120);
    imageView->setScene(imageScene);
    imageView->setSceneRect(0,0,118,118);
    imageView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    imageView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    image = new ImageItem(currentCellItem->image->pixmap());
    image->adjust(118,118);
    imageView->scene()->addItem(image);

    if(currentCellItem->nextCellItem == 0)
        nextImageButton->setDisabled(true);
    if(currentCellItem->previousCellItem == 0)
        previousImageButton->setDisabled(true);

    /********** Signals/Slots **************/

    this->connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
    this->connect(previousImageButton, SIGNAL(clicked()), this, SLOT(onPreviousImageClicked()));
    this->connect(nextImageButton, SIGNAL(clicked()), this, SLOT(onNextImageClicked()));

}

DialogProperties::~DialogProperties()
{
}

void DialogProperties::updateData()
{
    nameData->setText(QString("%1").arg(currentCellItem->getImageName()));
    widthData->setText(QString("%1 pixels").arg(currentCellItem->image->pixmap().width()));
    heightData->setText(QString("%1 pixels").arg(currentCellItem->image->pixmap().height()));
    typeData->setText(QString("%1").arg(currentCellItem->getImageType()));
    sizeData->setText(currentCellItem->enumSizeToQString());
    weightData->setText(QString("%1 Bytes").arg(QFile(QString("%1").arg(currentCellItem->getImagePath()+
                                                                        QDir().separator()+currentCellItem->getImageName()+
                                                                        "."+
                                                                        currentCellItem->getImageType())).size()));
    priceData->setText(QString("%1").arg(currentCellItem->getImagePrice()).append(QString::fromUtf8(" \u20AC")));
    cfdyData->setText(currentCellItem->enumCfdyToQString());
    pathData->setText(QString("%1").arg(currentCellItem->getImagePath()));
    image->setPixmap(currentCellItem->image->pixmap());
    image->adjust(118,118);

}

void DialogProperties::onPreviousImageClicked()
{
    if(currentCellItem->previousCellItem != 0){
        nextImageButton->setDisabled(false);
        currentCellItem = currentCellItem->previousCellItem;
        if(currentCellItem->previousCellItem == 0){
            nextImageButton->setDisabled(false);
            previousImageButton->setDisabled(true);
        }
    }
    this->updateData();
}

void DialogProperties::onNextImageClicked()
{
    if(currentCellItem->nextCellItem != 0 ){
        previousImageButton->setDisabled(false);
        currentCellItem = currentCellItem->nextCellItem;
        if(currentCellItem->nextCellItem == 0 ){
            nextImageButton->setDisabled(true);
            previousImageButton->setDisabled(false);
        }
    }
    this->updateData();
}
