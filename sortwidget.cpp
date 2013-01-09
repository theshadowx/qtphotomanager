#include "sortwidget.h"

/// Constructor of SortWidget
SortWidget::SortWidget(QWidget *parent) :
    QWidget(parent)
{

    /******** Price ************/
    priceFilter = new QLabel("Filter by price",this);

    priceFilter->setFont(QFont(QFont().defaultFamily(),10,QFont::Bold));
    priceFilter->setGeometry(20, 20, 1250*1/4,40);

    anyPrice = new QRadioButton("Any price",this);
    freePrice = new QRadioButton("Free",this);
    lowPrice = new QRadioButton(QString("Up to 100").append(QString::fromUtf8("\u20AC")),this);
    middlePrice = new QRadioButton(QString("100").append(QString::fromUtf8("\u20AC")).append(" - 1000").append(QString::fromUtf8("\u20AC")),this);
    highPrice = new QRadioButton(QString("Over 1000").append(QString::fromUtf8("\u20AC")),this);

    anyPrice->setGeometry(40,60,1250*1/4,20);
    freePrice->setGeometry(40,80,1250*1/4,20);
    lowPrice->setGeometry(40,100,1250*1/4,20);
    middlePrice->setGeometry(40,120,1250*1/4,20);
    highPrice->setGeometry(40,140,1250*1/4,20);

    priceButtonGroup = new QButtonGroup(this);
    priceButtonGroup->addButton(anyPrice,0);
    priceButtonGroup->addButton(freePrice,1);
    priceButtonGroup->addButton(lowPrice,2);
    priceButtonGroup->addButton(middlePrice,3);
    priceButtonGroup->addButton(highPrice,4);

    priceButtonGroup->setExclusive(true);
    priceButtonGroup->button(0)->setChecked(true);

    /********** Size *******/
    sizeFilter = new QLabel("Filter by size",this);

    sizeFilter->setFont(QFont(QFont().defaultFamily(),10,QFont::Bold));
    sizeFilter->setGeometry(20, 180, 1250*1/4,40);

    anySize = new QRadioButton("Any size",this);
    smallSize = new QRadioButton("Small",this);
    mediumSize = new QRadioButton("Medium",this);
    largeSize = new QRadioButton("Large",this);

    anySize->setGeometry(40,220,1250*1/4,20);
    smallSize->setGeometry(40,240,1250*1/4,20);
    mediumSize->setGeometry(40,260,1250*1/4,20);
    largeSize->setGeometry(40,280,1250*1/4,20);


    sizeButtonGroup = new QButtonGroup(this);
    sizeButtonGroup->addButton(anySize,0);
    sizeButtonGroup->addButton(smallSize,1);
    sizeButtonGroup->addButton(mediumSize,2);
    sizeButtonGroup->addButton(largeSize,3);

    sizeButtonGroup->setExclusive(true);
    sizeButtonGroup->button(0)->setChecked(true);

    /********** Type *******/
    typeFilter = new QLabel("Filter by type of image",this);

    typeFilter->setFont(QFont(QFont().defaultFamily(),10,QFont::Bold));
    typeFilter->setGeometry(20, 320, 1250*1/4,40);

    anyType = new QRadioButton("Any type",this);
    jpgType = new QRadioButton("JPEG",this);
    bmpType = new QRadioButton("BMP",this);
    pngType = new QRadioButton("PNG",this);
    otherType = new QRadioButton("Others",this);

    anyType->setGeometry(40,360,1250*1/4,20);
    jpgType->setGeometry(40,380,1250*1/4,20);
    bmpType->setGeometry(40,400,1250*1/4,20);
    pngType->setGeometry(40,420,1250*1/4,20);
    otherType->setGeometry(40,440,1250*1/4,20);

    typeButtonGroup = new QButtonGroup(this);
    typeButtonGroup->addButton(anyType,0);
    typeButtonGroup->addButton(jpgType,1);
    typeButtonGroup->addButton(bmpType,2);
    typeButtonGroup->addButton(pngType,3);
    typeButtonGroup->addButton(otherType,4);

    typeButtonGroup->setExclusive(true);
    typeButtonGroup->button(0)->setChecked(true);

}

SortWidget::~SortWidget()
{
}

/// Pain event callback
void SortWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

