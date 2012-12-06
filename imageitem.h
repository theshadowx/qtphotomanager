#ifndef IMAGEITEM_H
#define IMAGEITEM_H

#include <QtCore>
#include <QtGui>
#include <QtGui/QGraphicsPixmapItem>

class ImageItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    ImageItem(int id, const QPixmap &pixmap,QGraphicsItem *parent);

    void adjust();

protected:


private slots:


};

#endif
