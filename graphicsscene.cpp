#include "graphicsscene.h"
#include "graphicsview.h"
#include "cellitem.h"

/// Constructor of GraphicsScene
GraphicsScene::GraphicsScene(QObject *parent)
    : QGraphicsScene(parent)
{
    imageCellChain = 0;
    cellItemSelected = 0;

}

GraphicsScene::~GraphicsScene()
{
}
