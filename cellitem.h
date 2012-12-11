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
    void setId(int id);
    QString getImagePath() const;
    QString getImageName() const;
    int getImagePrice() const;
    int getId() const;

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

    ImageItem *image;
    CellItem *nextCellItem;
    CellItem *previousCellItem;

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);


private:

    QString imageName;
    QString imagePath;
    QString imageSource;
    int imagePrice;
    int id;
};

#endif // CELLITEM_H
