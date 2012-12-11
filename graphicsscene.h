#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QtGui>
#include <QtCore>
#include <QGraphicsScene>
#include "imagecellchain.h"


class graphicsScene : public QGraphicsScene
{

public:
    graphicsScene(QObject *parent);
    ImageCellChain *imageCellChain;
    CellItem *cellItemSelected;

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};
 
#endif // GRAPHICSSCENE_H
