#include "histogram.h"
#include "math.h"
#include <QGraphicsWidget>

Histogram::Histogram(QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
    type = GRAYSCALE;
}

Histogram::Histogram(const QImage imageSrc, int width, int height, TYPE type, QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
    this->width = width;
    this->height = height;
    this->type = type;
    this->imageSrc = imageSrc;
}

void Histogram::setSize(QSize size)
{
    height = size.height();
    width = size.width();
}

void Histogram::setHeight(int height)
{
    this->height = height;
}

void Histogram::setWidth(int width)
{
    this->width = width;
}

void Histogram::setSrcImage(QImage imageSrc)
{
    this->imageSrc = imageSrc;
}

void Histogram::setHistType(Histogram::TYPE type)
{
    this->type = type;
}

void Histogram::calculHistogram()
{
    QRgb value;
    QRgb valueRed;
    QRgb valueGreen;
    QRgb valueBlue;
    QRgb valueGray;

    mapRed = QVector<int>(256);
    mapGreen = QVector<int>(256);
    mapBlue = QVector<int>(256);
    mapGray = QVector<int>(256);

    for( int y = 0; y < imageSrc.height(); y++ ){
        for( int x = 0; x < imageSrc.width(); x++ ){
            value = imageSrc.pixel(x,y);
            valueRed = qRed(value);
            valueGreen = qGreen(value) ;
            valueBlue = qBlue(value);
            valueGray = qGray(value);

            mapRed[valueRed] = mapRed.value(valueRed) + 1;
            mapGreen[valueGreen] = mapGreen.value(valueGreen) + 1;
            mapBlue[valueBlue] = mapBlue.value(valueBlue) + 1;
            mapGray[valueGray] = mapGray.value(valueGray) + 1;
        }
    }

    int maxR = mapRed.data()[0];
    int maxG = mapGreen.data()[0];
    int maxB = mapBlue.data()[0];
    maxGray = mapGray.data()[0];
    maxColor = 0;

    for(int i=0; i<256; i++){
        if(maxR < mapRed.data()[i])
            maxR = mapRed.data()[i];

        if(maxG < mapGreen.data()[i])
            maxG = mapGreen.data()[i];

        if(maxB < mapBlue.data()[i])
            maxB = mapBlue.data()[i];

        if(maxGray < mapGray.data()[i])
            maxGray = mapGray.data()[i];
    }

    if(maxR < maxB){
        if(maxB < maxG){
            maxColor = maxG;
        }else{
            maxColor = maxB;
        }
    }else{
        if(maxG < maxR){
            maxColor = maxR;
        }else{
            maxColor = maxG;
        }
    }
}

Histogram::TYPE Histogram::getType()
{
    return type;
}

QRectF Histogram::boundingRect() const
{
    return QRect(0,0,width,height);
}

void Histogram::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{

    float ypace = 0.0;
    float xpace =(float) width/256.0;

    QPen pen;
    pen.setWidth(3);

    calculHistogram();

    if (type == COLOR){
        ypace = (float) height/maxColor;
        for(int i=0; i<255; i++){
            pen.setColor(QColor(255,0,0));
            painter->setPen(pen);
            painter->drawLine(QPoint(i*xpace,height - ypace * mapRed.data()[i]),QPoint((i+1)*xpace,height - ypace * mapRed.data()[i+1]));
            pen.setColor(QColor(0,255,0));
            painter->setPen(pen);
            painter->drawLine(QPoint(i*xpace,height - ypace * mapGreen.data()[i]),QPoint((i+1)*xpace,height - ypace * mapGreen.data()[i+1]));
            pen.setColor(QColor(0,0,255));
            painter->setPen(pen);
            painter->drawLine(QPoint(i*xpace,height - ypace * mapBlue.data()[i]),QPoint((i+1)*xpace,height - ypace * mapBlue.data()[i+1]));
         }
    }else if(type == GRAYSCALE){
        ypace = (float) height/maxGray;
        for(int i=0; i<256; i++){
            pen.setColor(QColor(0,0,0));
            painter->setPen(pen);
            painter->drawLine(QPoint(i*xpace,height),QPoint(i*xpace,height - ypace * mapGray.data()[i]));
        }
    }

    painter->setPen(QColor(0,0,0));
    painter->drawLine(QPoint(0,height),QPoint(255*xpace,height));
}

