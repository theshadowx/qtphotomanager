#include "cellitem.h"

CellItem::CellItem(int id, const QString fileName, const QString filePath, const int price, const QPixmap &pixmap,QGraphicsItem* parent)
    : QGraphicsItem(parent)
{

    imageName = fileName;
    imagePath = filePath;
    imagePrice = price;
    image = new ImageItem(id,pixmap,this);
}

QString CellItem::getImagePath()
{
    return imagePath;
}

QString CellItem::getImageName()
{
    return imageName;
}

int CellItem::getImagePrice()
{
    return imagePrice;
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
