#ifndef CELLITEM_H
#define CELLITEM_H

#include <QGraphicsItem>
#include <QtGui>
#include <QtCore>

#include "imageitem.h"

class CellItem:  public QGraphicsItem
{
public:
    CellItem(int id, const QString fileName, const QString filePath, const int price, const QPixmap &pixmap, QGraphicsItem *parent = 0);
    QString getImagePath();
    QString getImageName();
    int getImagePrice();

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

    ImageItem *image;

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);


private:

    CellItem *nextCellItem;
    CellItem *previousCellItem;

    QString imageName;
    QString imagePath;
    QString imageSource;
    int imagePrice;
    int imageNum;
};

#endif // CELLITEM_H
