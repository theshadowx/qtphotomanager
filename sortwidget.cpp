#include "sortwidget.h"

SortWidget::SortWidget(QWidget *parent) :
    QWidget(parent)
{
    resoFilter = new QLabel("Filter by resolution",this);

    resoFilter->setFont(QFont(QFont().defaultFamily(),10,QFont::Bold));
    resoFilter->setGeometry(20, 20, 1250*1/4,40);

    anyReso = new QRadioButton("Any resolution",this);
    smallReso = new QRadioButton("Small",this);
    mediumReso = new QRadioButton("Medium",this);
    largeReso = new QRadioButton("Large",this);

    anyReso->setGeometry(40,60,1250*1/4,20);
    smallReso->setGeometry(40,80,1250*1/4,20);
    mediumReso->setGeometry(40,100,1250*1/4,20);
    largeReso->setGeometry(40,120,1250*1/4,20);

    resoButtonGroup = new QButtonGroup(this);
    resoButtonGroup->addButton(anyReso,0);
    resoButtonGroup->addButton(smallReso,1);
    resoButtonGroup->addButton(mediumReso,2);
    resoButtonGroup->addButton(largeReso,3);

    resoButtonGroup->setExclusive(true);
    resoButtonGroup->button(0)->setChecked(true);

    /******** Price ************/
    priceFilter = new QLabel("Filter by price",this);

    priceFilter->setFont(QFont(QFont().defaultFamily(),10,QFont::Bold));
    priceFilter->setGeometry(20, 160, 1250*1/4,40);

    anyPrice = new QRadioButton("Any price",this);
    freePrice = new QRadioButton("Free",this);
    lowPrice = new QRadioButton(QString("Up to 100").append(QString::fromUtf8("\u20AC")),this);
    middlePrice = new QRadioButton(QString("100").append(QString::fromUtf8("\u20AC")).append(" - 1000").append(QString::fromUtf8("\u20AC")),this);
    highPrice = new QRadioButton(QString("Over 1000").append(QString::fromUtf8("\u20AC")),this);

    anyPrice->setGeometry(40,200,1250*1/4,20);
    freePrice->setGeometry(40,220,1250*1/4,20);
    lowPrice->setGeometry(40,240,1250*1/4,20);
    middlePrice->setGeometry(40,260,1250*1/4,20);
    highPrice->setGeometry(40,280,1250*1/4,20);

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
    sizeFilter->setGeometry(20, 320, 1250*1/4,40);

    anySize = new QRadioButton("Any size",this);
    smallSize = new QRadioButton("Up to 500 KB",this);
    mediumSize = new QRadioButton("500 KB - 1.5 MB",this);
    largeSize = new QRadioButton("Over 1.5 MB",this);

    anySize->setGeometry(40,360,1250*1/4,20);
    smallSize->setGeometry(40,380,1250*1/4,20);
    mediumSize->setGeometry(40,400,1250*1/4,20);
    largeSize->setGeometry(40,420,1250*1/4,20);


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
    typeFilter->setGeometry(20, 460, 1250*1/4,40);

    anyType = new QRadioButton("Any Type",this);
    jpgType = new QRadioButton("JPEG",this);
    bmpType = new QRadioButton("BMP",this);
    pngType = new QRadioButton("PNG",this);
    otherType = new QRadioButton("Others",this);

    anyType->setGeometry(40,500,1250*1/4,20);
    jpgType->setGeometry(40,520,1250*1/4,20);
    bmpType->setGeometry(40,540,1250*1/4,20);
    pngType->setGeometry(40,560,1250*1/4,20);
    otherType->setGeometry(40,580,1250*1/4,20);

    typeButtonGroup = new QButtonGroup(this);
    typeButtonGroup->addButton(anyType,0);
    typeButtonGroup->addButton(jpgType,1);
    typeButtonGroup->addButton(bmpType,2);
    typeButtonGroup->addButton(pngType,3);
    typeButtonGroup->addButton(otherType,4);

    typeButtonGroup->setExclusive(true);
    typeButtonGroup->button(0)->setChecked(true);

}
