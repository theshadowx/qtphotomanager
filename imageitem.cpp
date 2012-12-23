#include "imageitem.h"

ImageItem::ImageItem(QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent)
{
}

ImageItem::ImageItem(const QPixmap &pixmap, QGraphicsItem *parent)
    : QGraphicsPixmapItem(pixmap, parent)
{
    adjust();
}

void ImageItem::adjust()
{
    QMatrix matrix;
    matrix.scale(150/ boundingRect().width(), 120/ boundingRect().height());
    setMatrix(matrix);
}


void ImageItem::adjust(int sx, int sy)
{
    QMatrix matrix;
    matrix.scale(sx/ boundingRect().width(), sy/ boundingRect().height());
    setMatrix(matrix);
}


