#include "graphicsscene.h"
#include "graphicsview.h"
#include "cellitem.h"


GraphicsScene::GraphicsScene(QObject *parent)
    : QGraphicsScene(parent)
{
    imageCellChain = 0;
    cellItemSelected = 0;

}
