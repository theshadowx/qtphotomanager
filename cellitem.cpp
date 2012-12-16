#include "cellitem.h"

CellItem::CellItem()
{
    image = new ImageItem(this);
}

CellItem::CellItem(int id, const QString fileName, const QString filePath, const int price, const QPixmap &pixmap,QGraphicsItem* parent, IMAGE_CONFIDENTILITY confidentiality)
    : QGraphicsItem(parent)
{

    this->id = id;
    imageName = fileName;
    imagePath = filePath;
    imagePrice = price;
    imageCfdy = confidentiality;
    image = new ImageItem(pixmap,this);

}

void CellItem::setId(int id)
{
    this->id = id;
}

void CellItem::setImagePrice(int price)
{
    imagePrice = price;
}

void CellItem::setImageType(QString type)
{
    imageType = type;
}

void CellItem::setImagePath(QString path)
{
    imagePath = path;
}

void CellItem::setImageName(QString name)
{
    imageName = name;
}

void CellItem::setImageCfdy(CellItem::IMAGE_CONFIDENTILITY confidentiality)
{
    imageCfdy = confidentiality;
}

QString CellItem::getImagePath() const
{
    return imagePath;
}

QString CellItem::getImageName() const
{
    return imageName;
}

QString CellItem::getImageType() const
{
    return imageType;
}

CellItem::IMAGE_CONFIDENTILITY CellItem::getImageCfdy() const
{
   return imageCfdy;
}

int CellItem::getImagePrice() const
{
    return imagePrice;
}

int CellItem::getId() const
{
    return this->id;
}

QRectF CellItem::boundingRect() const
{
    return QRectF(0,0,150,170);
}

void CellItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{

    image->setPos(boundingRect().x(),boundingRect().y());
    painter->drawText(0,121,150,20,Qt::AlignCenter,imageName);
    painter->drawText(0,141,150,20,Qt::AlignCenter, QString::number(imagePrice).append(" ").append(QString::fromUtf8("\u20AC")));

}

void CellItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    event->ignore();
}


