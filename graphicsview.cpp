#include "graphicsview.h"

graphicsView::graphicsView(QWidget *parent)
    : QGraphicsView(parent)
{
    scene = new graphicsScene(this);
    scene->setSceneRect(-300, -300, 600, 600);
    setScene(scene);

    sceneProcessing = new graphicsScene(this);
    sceneProcessing->setSceneRect(-300, -300, 600, 600);

    this->setContextMenuPolicy(Qt::CustomContextMenu);
}
graphicsView::graphicsView(const QString &offices, const QString &images, QWidget *parent)
    : QGraphicsView(parent)
{
    scene = new graphicsScene(this);
    scene->setSceneRect(-300, -300, 600, 600);
    setScene(scene);

    sceneProcessing = new graphicsScene(this);
    sceneProcessing->setSceneRect(-300, -300, 600, 600);
}


void graphicsView::mousePressEvent(QMouseEvent* event)
{
    QGraphicsView::mousePressEvent(event);
}

void graphicsView::adjustCellItems()
{
    int itemsCount = scene->cellItemList.count();

    int imageOffsetHeight = 150;
    int imageOffsetWidth = 170;
    int leftMargin = 70;
    int topMargin = 40;
    int bottomMargin = 40;
    int columnCount =(int) (this->parentWidget()->frameSize().width()*3/4-leftMargin)/(imageOffsetWidth+leftMargin)+1;

    for(int i = 0; i < itemsCount; i++) {
        int columnOffset = (37 * (i % columnCount));
        int x = ((i % columnCount) * imageOffsetWidth) + leftMargin + columnOffset;
        int y = ((i / columnCount) * (imageOffsetHeight + bottomMargin)) + topMargin;

        scene->cellItemList.at(i)->setPos(this->mapToScene(x, y));
    }
}
