#include "cellitem.h"


/// Constructor of CellItem
CellItem::CellItem(QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
    image = new ImageItem(this);
    nextCellItem = 0;
    previousCellItem = 0;

    color = QColor(255, 255, 255);
    setFlag(ItemIsSelectable,true);

}

/// Copy constructor of CellItem
CellItem::CellItem(CellItem *cellItem, QGraphicsItem *parent)
: QGraphicsItem(parent)
{
    imageId = cellItem->getImageId();
    imageName = cellItem->getImageName();
    imagePath = cellItem->getImagePath();
    imagePrice = cellItem->getImagePrice();;
    imageCfdy = cellItem->getImageCfdy();
    imageType = cellItem->getImageType();
    imageSize = cellItem->getImageSize();
    image = new ImageItem(cellItem->image->pixmap(),this);

    color = QColor(255, 255, 255);

    nextCellItem =0;
    previousCellItem=0;

    setFlag(ItemIsSelectable,true);
}

/// Constructor of CellItem
CellItem::CellItem(int id,
                   const QString fileName,
                   const QString filePath,
                   const int price,
                   const QPixmap &pixmap,
                   QGraphicsItem* parent,
                   IMAGE_CONFIDENTIALITY confidentiality,
                   IMAGE_SIZE size)
    : QGraphicsItem(parent)
{
    imageId = id;
    imageName = fileName;
    imagePath = filePath;
    imagePrice = price;
    imageCfdy = confidentiality;
    imageSize = size;
    image = new ImageItem(pixmap,this);

    color = QColor(255, 255, 255);

    nextCellItem =0;
    previousCellItem=0;

    setFlag(ItemIsSelectable,true);
}

/// Destructor of CellItem
CellItem::~CellItem()
{
}

/// Get the bounding rectangle
QRectF CellItem::boundingRect() const
{
    return QRectF(0,0,150,170);
}

/// Paint the CellItem
void CellItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    image->setPos(this->boundingRect().x(),this->boundingRect().y());

    QRectF rect = boundingRect();
    painter->fillRect(rect,QBrush(color));
    painter->drawText(0,131,150,20,Qt::AlignCenter,imageName);
    painter->drawText(0,151,150,20,Qt::AlignCenter, QString::number(imagePrice).append(" ").append(QString::fromUtf8("\u20AC")));

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
    if (size==8)
    {
        int ssize = image->pixmap().height()*image->pixmap().width();

        if (ssize<=256*256){
            size = SMALL;
        }else if (ssize>=256*256 && ssize<=768*768){
            size = MEDIUM;
        }else if (ssize>=768*768){
            size = LARGE;
        }
    }
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

/// Convert the enum of image size to QString
QString CellItem::enumSizeToQString() const
{
    QString sizeQStr = "";
    switch (imageSize) {
        case SMALL :
            sizeQStr = "SMALL";
            break;
        case MEDIUM:
            sizeQStr = "MEDIUM";
            break;
        case LARGE:
            sizeQStr = "LARGE";
            break;
    default:
        sizeQStr = "";
        break;
    }
    return sizeQStr;
}

/// Convert the enum of image confidentiality to QString
QString CellItem::enumCfdyToQString() const
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
        break;
    }
    return cfdyQStr;
}

CellItem::IMAGE_SIZE CellItem::qstringToEnumSize(QString sizeQStr)
{
    if(sizeQStr == "SMALL"){
        imageSize = SMALL;
    }else if(sizeQStr == "MEDIUM"){
        imageSize = MEDIUM;
    }else if(sizeQStr == "LARGE"){
        imageSize = LARGE;
    }
    return imageSize;
}

CellItem::IMAGE_CONFIDENTIALITY CellItem::qstringToEnumCfdy(QString cfdyQStr)
{
    if(cfdyQStr == "F") {
        imageCfdy = F;
    }else if(cfdyQStr == "R") {
        imageCfdy = R;
    }
    return imageCfdy;
}
