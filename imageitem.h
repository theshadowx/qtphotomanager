#ifndef IMAGEITEM_H
#define IMAGEITEM_H

#include <QtCore>
#include <QtGui>
#include <QtGui/QGraphicsPixmapItem>

class ImageItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    /*!
     *
     */
    ImageItem(QGraphicsItem *parent = 0);
    /*!
     *
     */
    ImageItem(const QPixmap &pixmap,QGraphicsItem *parent = 0);

    /*!
     *
     */
    void adjust();


    /*!
     *
     */
    void adjust(int sx, int sy);

};

#endif
