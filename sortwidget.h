#ifndef SORTWIDGET_H
#define SORTWIDGET_H

#include <QWidget>
#include <QtGui>
#include <QtCore>
#include "graphicsview.h"

class SortWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SortWidget(QWidget *parent = 0);
    graphicsView *view;

signals:
    
public slots:

private:
    QLabel *resoFilter;
    QLabel *priceFilter;
    QLabel *sizeFilter;
    QLabel *typeFilter;

    QButtonGroup *resoButtonGroup;
    QButtonGroup *priceButtonGroup;
    QButtonGroup *sizeButtonGroup;
    QButtonGroup *typeButtonGroup;

    QRadioButton *anyReso;
    QRadioButton *smallReso;
    QRadioButton *mediumReso;
    QRadioButton *largeReso;

    QRadioButton *anyPrice;
    QRadioButton *freePrice;
    QRadioButton *lowPrice;
    QRadioButton *middlePrice;
    QRadioButton *highPrice;

    QRadioButton *anySize;
    QRadioButton *smallSize;
    QRadioButton *mediumSize;
    QRadioButton *largeSize;

    QRadioButton *anyType;
    QRadioButton *jpgType;
    QRadioButton *bmpType;
    QRadioButton *pngType;
    QRadioButton *otherType;

    
};

#endif // SORTWIDGET_H
