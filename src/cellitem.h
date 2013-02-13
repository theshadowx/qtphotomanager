#ifndef CELLITEM_H
#define CELLITEM_H

#include "imageitem.h"
#include <QGraphicsDropShadowEffect>
#include <QPainter>

class CellItem:  public QGraphicsItem
{
public:

    enum IMAGE_CONFIDENTIALITY{F=0, R=1};
    enum IMAGE_SIZE{SMALL=0, MEDIUM=1, LARGE=2};

    CellItem(QGraphicsItem *parent = 0);
    CellItem(CellItem* cellItem, QGraphicsItem *parent = 0);
    CellItem(int id,
             const QString fileName,
             const QString filePath,
             const int price,
             const QPixmap &pixmap,
             QGraphicsItem *parent = 0,
             IMAGE_CONFIDENTIALITY confidentiality = R,
             IMAGE_SIZE size = MEDIUM);

    virtual ~CellItem();

    void setImageId(int id);
    void setImagePrice(int price);
    void setImageType(QString type);
    void setImagePath(QString path);
    void setImageName(QString name);
    void setImageCfdy(IMAGE_CONFIDENTIALITY confidentiality);
    void setImageSize(IMAGE_SIZE size);
    void setColor(QColor c);

    int getImageId() const;
    int getImagePrice() const;
    QString getImagePath() const;
    QString getImageName() const;
    QString getImageType() const;
    IMAGE_CONFIDENTIALITY getImageCfdy() const;
    IMAGE_SIZE getImageSize() const;

    QString enumSizeToQString() const;
    QString enumCfdyToQString() const;

    CellItem::IMAGE_SIZE qstringToEnumSize(QString sizeQStr);
    CellItem::IMAGE_CONFIDENTIALITY qstringToEnumCfdy(QString cfdyQStr);

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *,
                       QWidget *);

    ImageItem *image;
    CellItem *nextCellItem;
    CellItem *previousCellItem;

private:
    QColor color;
    QGraphicsDropShadowEffect* shadow;
    QString imageName;
    QString imagePath;
    QString imageType;
    IMAGE_SIZE imageSize;
    IMAGE_CONFIDENTIALITY imageCfdy;
    int imagePrice;
    int imageId;
};

#endif // CELLITEM_H
