#ifndef CELLITEM_H
#define CELLITEM_H

#include "imageitem.h"

class CellItem:  public QGraphicsItem
{
public:

    enum IMAGE_CONFIDENTILITY{F=0,R=1};

    CellItem();
    CellItem(int id, const QString fileName, const QString filePath, const int price, const QPixmap &pixmap, QGraphicsItem *parent = 0, IMAGE_CONFIDENTILITY confidentiality = R);

    void setId(int id);
    void setImagePrice(int price);
    void setImageType(QString type);
    void setImagePath(QString path);
    void setImageName(QString name);
    void setImageCfdy(IMAGE_CONFIDENTILITY confidentiality);

    int getId() const;
    int getImagePrice() const;
    QString getImagePath() const;
    QString getImageName() const;
    QString getImageType() const;
    IMAGE_CONFIDENTILITY getImageCfdy() const;


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
    QString imageType;
    IMAGE_CONFIDENTILITY imageCfdy;
    int imagePrice;
    int id;
};

#endif // CELLITEM_H
