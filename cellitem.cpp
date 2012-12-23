#include "cellitem.h"

CellItem::CellItem()
{
    image = new ImageItem(this);
    nextCellItem =0;
    previousCellItem=0;
}

CellItem::CellItem(int id, const QString fileName, const QString filePath, const int price, const QPixmap &pixmap,QGraphicsItem* parent, IMAGE_CONFIDENTIALITY confidentiality,IMAGE_SIZE size)
    : QGraphicsItem(parent)
{

    this->id = id;
    imageName = fileName;
    imagePath = filePath;
    imagePrice = price;
    imageCfdy = confidentiality;
    imageSize = size;
    image = new ImageItem(pixmap,this);

    nextCellItem =0;
    previousCellItem=0;

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

void CellItem::setImageRt(CellItem::IMAGE_CONFIDENTIALITY confidentiality)
{
    imageCfdy = confidentiality;
}

void CellItem::setImageSize(CellItem::IMAGE_SIZE size)
{
    imageSize = size;
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

CellItem::IMAGE_CONFIDENTIALITY CellItem::getImageCfdy() const
{
    return imageCfdy;
}

CellItem::IMAGE_SIZE CellItem::getImageSize() const
{
    return (CellItem::IMAGE_SIZE) imageSize;
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

QString CellItem::enumSizeToQString()
{
    QString sizeQStr = "";
    switch (imageSize) {
        case SMALL :
            sizeQStr = "Small";
            break;
        case MEDIUM:
            sizeQStr = "Medium";
            break;
        case LARGE:
            sizeQStr = "Large";
            break;
    default:
        sizeQStr = "";
    }

    return sizeQStr;
}

QString CellItem::enumCfdyToQString()
{
    QString cfdyQStr;
    switch (imageCfdy) {
        case F :
            cfdyQStr = "F";
            break;
        case R:
            cfdyQStr = "R";
            break;
    default:
        cfdyQStr = "";
    }

    return cfdyQStr;
}


