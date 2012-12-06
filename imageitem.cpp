#include "imageitem.h"

ImageItem::ImageItem(int id, const QPixmap &pixmap, QGraphicsItem *parent)
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



