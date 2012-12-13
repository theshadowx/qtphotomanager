#ifndef CELLITEM_H
#define CELLITEM_H

#include "imageitem.h"

class CellItem:  public QGraphicsItem
{
public:
    CellItem(int id, const QString fileName, const QString filePath, const int price, const QPixmap &pixmap, QGraphicsItem *parent = 0);
    void setId(int id);
    void setImageType(QString imageType);
    QString getImagePath() const;
    QString getImageName() const;
    QString getImageType() const;
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
    QString imageType;
    int imagePrice;
    int id;
};

#endif // CELLITEM_H
