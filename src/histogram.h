#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <QGraphicsItem>
#include <QPainter>

class Histogram : public QGraphicsItem
{
public:

    enum TYPE{GRAYSCALE=0, COLOR=1};

    Histogram(QGraphicsItem *parent = 0);
    explicit Histogram(const QImage imageSrc,
                       int width,
                       int height,
                       TYPE type = GRAYSCALE,
                       QGraphicsItem *parent = 0);

    void setSize(QSize size);
    void setHeight(int height);
    void setWidth(int width);
    void setSrcImage(QImage imageSrc);
    void setHistType(TYPE type);
    void calculHistogram();

    TYPE getType();

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *,
                       QWidget *);

private:

    QImage imageSrc;

    QVector<int> mapRed;
    QVector<int> mapGreen;
    QVector<int> mapBlue;
    QVector<int> mapGray;

    int width;
    int height;
    TYPE type;

    int maxColor;
    int maxGray;

};

#endif // HISTOGRAM_H
