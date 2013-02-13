#ifndef PIECHART_H
#define PIECHART_H

#include <QGraphicsItem>
#include <QPainter>
#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include "imagecellchain.h"


class PieChart : public QGraphicsItem
{

public:
    explicit PieChart (QGraphicsItem *parent = 0);
    virtual ~PieChart();

    void buildAChart( QString param, int total, int var1, int var2, int var3);
    void setWidth(const int width);
    void setHeight(const int height);
    void setSize(const QSize size);

    ImageCellChain *chain;
    int startAngle;
    int spanAngle;

    int jpgCount;
    int bmpCount;
    int pngCount;

    int smallCount;
    int mediumCount;
    int largeCount;

    int RCount;
    int FCount;

    int lowCount;
    int averageCount;
    int highCount;

    int totalCount;

    QString parameter;
    QLabel *pieChartCaption;

    int width;
    int height;

protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    virtual QRectF boundingRect() const;
};

#endif // PIECHART_H
