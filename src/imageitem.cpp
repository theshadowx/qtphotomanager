#include "imageitem.h"
#include <QGraphicsSceneMouseEvent>

/// Constructor of ImageItem
ImageItem::ImageItem(QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent)
{
    this->setCacheMode(NoCache);
}

/// Constructor of ImageItem
ImageItem::ImageItem(const QPixmap &pixmap, QGraphicsItem *parent)
    : QGraphicsPixmapItem(pixmap, parent)
{
    this->setCacheMode(NoCache);
    this->adjust();
}

ImageItem::~ImageItem()
{
     QPixmapCache::clear();
}

/// Adjust an ImageItem in a frame
void ImageItem::adjust()
{
    QMatrix matrix;
    matrix.scale(150/boundingRect().width(), 120/boundingRect().height());
    this->setMatrix(matrix);
}

/// Ajust an ImageItem in a frame
void ImageItem::adjust(int sx, int sy)
{
    QMatrix matrix;
    matrix.scale(sx/ boundingRect().width(), sy/ boundingRect().height());
    this->setMatrix(matrix);
}

