#include "cellitem.h"

CellItem::CellItem(int id, const QString fileName, const QString filePath, const int price, const QPixmap &pixmap,QGraphicsItem* parent)
    : QGraphicsItem(parent)
{

    imageName = fileName;
    imagePath = filePath;
    imagePrice = price;
    image = new ImageItem(pixmap,this);
    this->id = id;
}

void CellItem::setId(int id)
{
    this->id = id;
}

void CellItem::setImageType(QString imageType)
{
    this->imageType = imageType;
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
