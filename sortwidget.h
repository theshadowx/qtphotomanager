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
    virtual ~SortWidget();

    GraphicsView *view;

protected:
    void paintEvent(QPaintEvent *);

private:
    QLabel *priceFilter;
    QLabel *sizeFilter;
    QLabel *typeFilter;

    QButtonGroup *priceButtonGroup;
    QButtonGroup *sizeButtonGroup;
    QButtonGroup *typeButtonGroup;

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
