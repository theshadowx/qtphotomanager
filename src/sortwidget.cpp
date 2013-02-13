#include "sortwidget.h"
#include "minmaxdialog.h"

/// Constructor of SortWidget
SortWidget::SortWidget(QWidget *parent) :
    QWidget(parent)
{
    /// ******** Price ************ ///
    priceFilter = new QLabel("Price",this);

    priceFilter->setFont(QFont(QFont().defaultFamily(),10,QFont::Bold));

    anyPrice = new QRadioButton("Any price",this);
    freePrice = new QRadioButton("Free",this);
    lowPrice = new QRadioButton(QString("Up to 100").append(QString::fromUtf8("\u20AC")),this);
    middlePrice = new QRadioButton(QString("100").append(QString::fromUtf8("\u20AC")).append(" - 1000").append(QString::fromUtf8("\u20AC")),this);
    highPrice = new QRadioButton(QString("Over 1000").append(QString::fromUtf8("\u20AC")),this);
    rangePrice = new QRadioButton("Choose range",this);

    priceButtonGroup = new QButtonGroup(this);
    priceButtonGroup->addButton(anyPrice,0);
    priceButtonGroup->addButton(freePrice,1);
    priceButtonGroup->addButton(lowPrice,2);
    priceButtonGroup->addButton(middlePrice,3);
    priceButtonGroup->addButton(highPrice,4);
    priceButtonGroup->addButton(rangePrice,5);

    priceButtonGroup->setExclusive(true);
    priceButtonGroup->button(0)->setChecked(true);

    /// ********** Size ******* ///
    sizeFilter = new QLabel("Size",this);

    sizeFilter->setFont(QFont(QFont().defaultFamily(),10,QFont::Bold));

    anySize = new QRadioButton("Any size",this);
    smallSize = new QRadioButton("Small",this);
    mediumSize = new QRadioButton("Medium",this);
    largeSize = new QRadioButton("Large",this);

    sizeButtonGroup = new QButtonGroup(this);
    sizeButtonGroup->addButton(anySize,0);
    sizeButtonGroup->addButton(smallSize,1);
    sizeButtonGroup->addButton(mediumSize,2);
    sizeButtonGroup->addButton(largeSize,3);

    sizeButtonGroup->setExclusive(true);
    sizeButtonGroup->button(0)->setChecked(true);

    /// ********** Type ******* ///
    typeFilter = new QLabel("Type",this);

    typeFilter->setFont(QFont(QFont().defaultFamily(),10,QFont::Bold));

    anyType = new QRadioButton("Any type",this);
    jpgType = new QRadioButton("JPEG",this);
    bmpType = new QRadioButton("BMP",this);
    pngType = new QRadioButton("PNG",this);

    typeButtonGroup = new QButtonGroup(this);
    typeButtonGroup->addButton(anyType,0);
    typeButtonGroup->addButton(jpgType,1);
    typeButtonGroup->addButton(bmpType,2);
    typeButtonGroup->addButton(pngType,3);

    typeButtonGroup->setExclusive(true);
    typeButtonGroup->button(0)->setChecked(true);

    /// ******** Sorting ************ ///
    Orderfilter = new QLabel("Sort...",this);

    Orderfilter->setFont(QFont(QFont().defaultFamily(),10,QFont::Bold));

    priceOrder = new QRadioButton("By price",this);
    alphabetOrder = new QRadioButton("By alphabetical order",this);
    sizeOrder = new QRadioButton("By size",this);

    orderButtonGroup = new QButtonGroup(this);
    orderButtonGroup->addButton(priceOrder,0);
    orderButtonGroup->addButton(alphabetOrder,1);
    orderButtonGroup->addButton(sizeOrder,2);

    orderButtonGroup->setExclusive(true);
    orderButtonGroup->button(0)->setChecked(true);

    /// *************** Connection SLOT/SIGNAL ***************** ///
    QObject::connect(sizeButtonGroup,SIGNAL(buttonClicked(QAbstractButton*)),this,SLOT(sortImages()));
    QObject::connect(priceButtonGroup, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(sortImages()));
    QObject::connect(typeButtonGroup,SIGNAL(buttonClicked(QAbstractButton*)),this,SLOT(sortImages()));
    QObject::connect(orderButtonGroup,SIGNAL(buttonClicked(QAbstractButton*)),this,SLOT(sortByOrder(QAbstractButton*)));
}

SortWidget::~SortWidget()
{
}

void SortWidget::resizeEvent(QResizeEvent *)
{
    priceFilter->setGeometry(20, 20, this->frameSize().width()-20,40);
    anyPrice->setGeometry(40,60,this->frameSize().width()-40,20);
    freePrice->setGeometry(40,80,this->frameSize().width()-40,20);
    lowPrice->setGeometry(40,100,this->frameSize().width()-40,20);
    middlePrice->setGeometry(40,120,this->frameSize().width()-40,20);
    highPrice->setGeometry(40,140,this->frameSize().width()-40,20);
    rangePrice->setGeometry(40,160,1250*1/4,20);

    sizeFilter->setGeometry(20, 200, this->frameSize().width()-20,40);
    anySize->setGeometry(40,240,this->frameSize().width()-40,20);
    smallSize->setGeometry(40,260,this->frameSize().width()-40,20);
    mediumSize->setGeometry(40,280,this->frameSize().width()-40,20);
    largeSize->setGeometry(40,300,this->frameSize().width()-40,20);

    typeFilter->setGeometry(20, 340, this->frameSize().width()-20,40);
    anyType->setGeometry(40,380,this->frameSize().width()-40,20);
    jpgType->setGeometry(40,400,this->frameSize().width()-40,20);
    bmpType->setGeometry(40,420,this->frameSize().width()-40,20);
    pngType->setGeometry(40,440,this->frameSize().width()-40,20);


    Orderfilter->setGeometry(20, 480, 1250*1/4,40);
    priceOrder->setGeometry(40,520,1250*1/4,20);
    alphabetOrder->setGeometry(40,540,1250*1/4,20);
    sizeOrder->setGeometry(40,560,1250*1/4,20);
}

/// Pain event callback
void SortWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void SortWidget::sortImages()
{
    QAbstractButton *button = 0;
    QList<CellItem*> cellList;

    for(int i=0; i<imageCellChain->getCount();i++)
        cellList.append(imageCellChain->cellItemAt(i));

    /// ********** Sort images by price ********** ///
    button = priceButtonGroup->checkedButton();

    /// Any price is chosen
    if(button == anyPrice){

        /// Free is chosen
    }else if(button == freePrice){
        for(int i=0;i<cellList.length();i++){
            if(cellList.at(i)->getImagePrice()!=0){
                cellList.removeAt(i);
                i--;
            }
        }
        /// Price under 100
    }else if(button == lowPrice){
        for(int i=0;i<cellList.length();i++){
            if(cellList.at(i)->getImagePrice()>100){
                cellList.removeAt(i);
                i--;
            }
        }

        /// Price between 100 and 1000
    }else if(button == middlePrice){
        for(int i=0;i<cellList.length();i++){
            if(cellList.at(i)->getImagePrice()<=100 || cellList.at(i)->getImagePrice()>1000){
                cellList.removeAt(i);
                i--;
            }
        }

        /// Price higher than 1000
    }else if(button == highPrice){
        for(int i=0;i<cellList.length();i++){
            if(cellList.at(i)->getImagePrice()<=1000){
                cellList.removeAt(i);
                i--;
            }
        }
    }else if(button == rangePrice){
        MinMax minMax(this);
        int prixMax;
        int prixMin;
        if(minMax.exec()){
            prixMax = minMax.priceMax;
            prixMin = minMax.priceMin;
            for(int i=0;i<cellList.length();i++){
                if(cellList.at(i)->getImagePrice()<prixMin || cellList.at(i)->getImagePrice()>prixMax ){
                    cellList.removeAt(i);
                    i--;
                }
            }
        }else{
            priceButtonGroup->button(0)->setChecked(true);
        }
    }

    /// ********** Sort images by siz ********** ///
    button = sizeButtonGroup->checkedButton();
    /// Any Size is chosen
    if(button == anySize){

        /// Small size is chosen
    }else if(button == smallSize){
        for(int i=0;i<cellList.length();i++){
            if(cellList.at(i)->getImageSize() != CellItem::SMALL){
                cellList.removeAt(i);
                i--;
            }
        }

        /// Medium Size is chosen
    }else if(button == mediumSize ){
        for(int i=0;i<cellList.length();i++){
            if(cellList.at(i)->getImageSize()  != CellItem::MEDIUM){
                cellList.removeAt(i);
                i--;
            }
        }
        /// Large Size is chosen
    }else if(button == largeSize){
        for(int i=0;i<cellList.length();i++){
            if(cellList.at(i)->getImageSize()  !=  CellItem::LARGE){
                cellList.removeAt(i);
                i--;
            }
        }
    }

    /// ********** Sort images by type ********** ///
    button = typeButtonGroup->checkedButton();

    /// Any type is chosen
    if(button == anyType){

        /// png is chosen
    }else if(button == pngType){
        for(int i=0;i<cellList.length();i++){
            if(cellList.at(i)->getImageType() != "png"){
                cellList.removeAt(i);
                i--;
            }
        }
        /// jpeg is chosen
    }else if(button == jpgType){
        for(int i=0;i<cellList.length();i++){
            if(cellList.at(i)->getImageType() != "jpg"){
                cellList.removeAt(i);
                i--;
            }
        }

        /// bmp is chosen
    }else if(button == bmpType){
        for(int i=0;i<cellList.length();i++){
            if(cellList.at(i)->getImageType() != "bmp"){
                cellList.removeAt(i);
                i--;
            }
        }
    }

    for(int i=0;i<imageCellChain->getCount();i++){
        if(view->scene->items().contains(imageCellChain->cellItemAt(i)))
            view->scene->removeItem(imageCellChain->cellItemAt(i));
    }

    for (int i=0;i<cellList.length();i++)
        view->scene->addItem(cellList.at(i));
    view->adjustCellItems();
}

void SortWidget::sortByOrder(QAbstractButton *button)
{
    for(int i=0;i<imageCellChain->getCount();i++){
        if(view->scene->items().contains(imageCellChain->cellItemAt(i)))
            view->scene->removeItem(imageCellChain->cellItemAt(i));
    }
    /// price order is chosen
    if(button == priceOrder){
        bool ordre = false;
        int a =imageCellChain->getCount();
        while(!ordre){
            ordre= true;
            for(int i=0;i<a-1;i++){
                if (imageCellChain->cellItemAt(i)->getImagePrice()>imageCellChain->cellItemAt(i+1)->getImagePrice()){
                    imageCellChain->swap(imageCellChain->cellItemAt(i),imageCellChain->cellItemAt(i+1));
                    ordre =false;
                }
            }
            a=a-1;
        }

        /// alphabet order is chosen
    }else if(button == alphabetOrder){
        bool ordre = false;
        int a =imageCellChain->getCount();
        while(!ordre){
            ordre= true;
            for(int i=0;i<a-1;i++){
                if (imageCellChain->cellItemAt(i)->getImageName().toLower()>imageCellChain->cellItemAt(i+1)->getImageName().toLower()){
                    imageCellChain->swap(imageCellChain->cellItemAt(i),imageCellChain->cellItemAt(i+1));
                    ordre =false;
                }
            }
            a=a-1;
        }

        /// size order is chosen
    }else if(button == sizeOrder){
        bool ordre = false;
        int a =imageCellChain->getCount();
        while(!ordre){
            ordre= true;
            for(int i=0;i<a-1;i++){
                if (imageCellChain->cellItemAt(i)->getImageSize()>imageCellChain->cellItemAt(i+1)->getImageSize()){
                    imageCellChain->swap(imageCellChain->cellItemAt(i),imageCellChain->cellItemAt(i+1));
                    ordre =false;
                }
            }
            a=a-1;
        }
    }

    for(int i=0;i<imageCellChain->getCount();i++)
        view->scene->addItem(imageCellChain->cellItemAt(i));
    view->adjustCellItems();

    sizeButtonGroup->button(0)->setChecked(true);
    priceButtonGroup->button(0)->setChecked(true);
    typeButtonGroup->button(0)->setChecked(true);

}

