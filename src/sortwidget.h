#ifndef SORTWIDGET_H
#define SORTWIDGET_H

#include "graphicsview.h"

#include <QWidget>
#include <QLabel>
#include <QButtonGroup>
#include <QRadioButton>
#include <QStyleOption>
#include <QStyle>

class SortWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SortWidget(QWidget *parent = 0);
    virtual ~SortWidget();

    GraphicsView *view;
    ImageCellChain *imageCellChain;

protected:
    void resizeEvent(QResizeEvent *);
    void paintEvent(QPaintEvent *);

private:
    QLabel *priceFilter;
    QLabel *sizeFilter;
    QLabel *typeFilter;
    QLabel *Orderfilter;

    QButtonGroup *priceButtonGroup;
    QButtonGroup *sizeButtonGroup;
    QButtonGroup *typeButtonGroup;
    QButtonGroup *orderButtonGroup;

    QRadioButton *anyPrice;
    QRadioButton *freePrice;
    QRadioButton *lowPrice;
    QRadioButton *middlePrice;
    QRadioButton *highPrice;
    QRadioButton *rangePrice;

    QRadioButton *anySize;
    QRadioButton *smallSize;
    QRadioButton *mediumSize;
    QRadioButton *largeSize;

    QRadioButton *anyType;
    QRadioButton *jpgType;
    QRadioButton *bmpType;
    QRadioButton *pngType;

    QRadioButton *priceOrder;
    QRadioButton *alphabetOrder;
    QRadioButton *sizeOrder;

public slots:
    void sortImages();
    void sortByOrder(QAbstractButton * button);

};

#endif // SORTWIDGET_H
