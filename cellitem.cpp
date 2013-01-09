#include "cellitem.h"

/// Constructor of CellItem
CellItem::CellItem()
{
    image = new ImageItem(this);
    color = QColor(255, 255, 255);
    nextCellItem =0;
    previousCellItem=0;

    setFlag(ItemIsSelectable,true);
}

/// Constructor of CellItem
CellItem::CellItem(int id, const QString fileName, const QString filePath, const int price, const QPixmap &pixmap,QGraphicsItem* parent, IMAGE_CONFIDENTIALITY confidentiality,IMAGE_SIZE size)
    : QGraphicsItem(parent)
{
    imageId = id;
    imageName = fileName;
    imagePath = filePath;
    imagePrice = price;
    imageCfdy = confidentiality;
    imageSize = size;
    image = new ImageItem(pixmap,this);

    nextCellItem =0;
    previousCellItem=0;

    color = QColor(255, 255, 255);
    setFlag(ItemIsSelectable,true);
}

/// Destructor of CellItem
CellItem::~CellItem()
{
}

/// Set the index of the image
void CellItem::setImageId(int id)
{
    imageId = id;
}

/// Set the price of the image
void CellItem::setImagePrice(int price)
{
    imagePrice = price;
}

/// Set the type of the image
void CellItem::setImageType(QString type)
{
    imageType = type;
}

/// Set the path of the image
void CellItem::setImagePath(QString path)
{
    imagePath = path;
}

/// Set the name of the image
void CellItem::setImageName(QString name)
{
    imageName = name;
}


/// Set confidentiality of the image
void CellItem::setImageCfdy(CellItem::IMAGE_CONFIDENTIALITY confidentiality)
{
    imageCfdy = confidentiality;
}

/// Set the size of the image
void CellItem::setImageSize(CellItem::IMAGE_SIZE size)
{
    imageSize = size;
}

/// Set the color of the CellItem
void CellItem::setColor(QColor c)
{
    color = c;
}

/// Get the path of the image
QString CellItem::getImagePath() const
{
    return imagePath;
}

/// Get the name of the image
QString CellItem::getImageName() const
{
    return imageName;
}

/// Get the type of the image
QString CellItem::getImageType() const
{
    return imageType;
}

/// Get the confidentiality of the image
CellItem::IMAGE_CONFIDENTIALITY CellItem::getImageCfdy() const
{
    return imageCfdy;
}

/// Get the image size
CellItem::IMAGE_SIZE CellItem::getImageSize() const
{
    return (CellItem::IMAGE_SIZE) imageSize;
}

/// Get the image price
int CellItem::getImagePrice() const
{
    return imagePrice;
}

/// Get the image index
int CellItem::getImageId() const
{
    return imageId;
}

/// Get the bounding rectangle
QRectF CellItem::boundingRect() const
{
    return QRectF(0,0,150,170);
}

/// Paint the CellItem
void CellItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{

    image->setPos(boundingRect().x(),boundingRect().y());
    QRectF rect = boundingRect();
    painter->fillRect(rect,QBrush(color));
    painter->drawText(0,121,150,20,Qt::AlignCenter,imageName);
    painter->drawText(0,141,150,20,Qt::AlignCenter, QString::number(imagePrice).append(" ").append(QString::fromUtf8("\u20AC")));

}

/// Convert the enum of image size to QString
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

/// Convert the enum of image confidentiality to QString
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

