#include "graphicsscene.h"
#include "graphicsview.h"
#include "cellitem.h"


graphicsScene::graphicsScene(QObject *parent = 0)
    : QGraphicsScene(parent)
{
}

void graphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

}

void graphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

    QGraphicsScene::mouseReleaseEvent(event);
}

