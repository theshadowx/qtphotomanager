#include "graphicsview.h"

/// Constructor of GraphicsView
GraphicsView::GraphicsView(QWidget *parent)
    : QGraphicsView(parent)
{
    scene = new GraphicsScene(this);
    scene->setSceneRect(-300, -300, 600, 600);
    setScene(scene);

    sceneProcessing = new GraphicsScene(this);
    sceneProcessing->setSceneRect(-300, -300, 600, 600);

    this->setContextMenuPolicy(Qt::CustomContextMenu);
}

GraphicsView::~GraphicsView()
{
}

/// Ajust the CellItems in the View
void GraphicsView::adjustCellItems()
{
    int itemsCount = scene->imageCellChain->getCount();

    int imageOffsetHeight = 150;
    int imageOffsetWidth = 170;
    int leftMargin = 70;
    int topMargin = 40;
    int bottomMargin = 40;
    int columnCount =(int) (this->parentWidget()->frameSize().width()*3/4-leftMargin)/(imageOffsetWidth+leftMargin)+1;
    int lineCount = (int)  (itemsCount/columnCount);

    int rectHeight = lineCount *(topMargin + bottomMargin + imageOffsetHeight);

    this->verticalScrollBar()->setValue(this->verticalScrollBar()->minimum());

    scene->setSceneRect(mapFromGlobal(QPoint(0,0)).x(),
                        mapFromGlobal(QPoint(0,0)).y(),
                        this->parentWidget()->frameSize().width()*3/4-25,
                        rectHeight);

    for(int i = 0; i < itemsCount; i++) {
        int columnOffset = (37 * (i % columnCount));
        int x = ((i % columnCount) * imageOffsetWidth) + leftMargin + columnOffset;
        int y = ((i / columnCount) * (imageOffsetHeight + bottomMargin)) + topMargin;

        scene->imageCellChain->cellItemAt(i)->setPos(this->mapToScene(x, y));
    }
}

/// Mouse double click event callback
void GraphicsView::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(currentUser->getPermission() == Users::LEVEL_1){
        if(this->QGraphicsView::scene() == this->scene){
            if(event->button() == Qt::LeftButton){
                CellItem *item = static_cast<CellItem*> (this->scene->itemAt(this->mapToScene(event->pos())));
                if(item!=NULL){
                    if(scene->imageCellChain->contains(item)){
                        scene->cellItemSelected  = item;
                        emit cellItemClicked(item);
                    }else{
                        CellItem *itemParent = static_cast<CellItem*> (item->parentItem());
                        scene->cellItemSelected  = itemParent;
                        emit cellItemClicked(itemParent);
                    }

                    this->resize(this->parentWidget()->size().width()*3/4,this->parentWidget()->size().height());
                    this->setScene(sceneProcessing);
                    scene->removeItem(scene->cellItemSelected);
                    sceneProcessing->addItem(scene->cellItemSelected->image);
                    sceneProcessing->cellItemSelected = scene->cellItemSelected;
                    this->fitInView(scene->cellItemSelected->image,Qt::KeepAspectRatio);
                    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
                    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
                }
            }
        }
    }
    QGraphicsView::mouseDoubleClickEvent(event);
}

/// Mouse press event callback
void GraphicsView::mousePressEvent(QMouseEvent *event)
{

    QList<QGraphicsItem *> cellItemList = this->scene->selectedItems();
    for(int i=0; i<cellItemList.length();i++){
        CellItem* cellItem = static_cast<CellItem*> (cellItemList.at(i));
        cellItem->setColor(QColor(255,255,255));
        cellItem->setSelected(false);
    }

    if(this->QGraphicsView::scene() == this->scene){
        if(event->button() == Qt::LeftButton){
            CellItem *item = static_cast<CellItem*> (this->scene->itemAt(this->mapToScene(event->pos())));
            if(item!=NULL){
                if(scene->imageCellChain->contains(item)){
                    item->setColor(QColor(135,135,135));
                    item->setSelected(true);
                }else{
                    CellItem *itemParent = static_cast<CellItem*> (item->parentItem());
                    itemParent->setColor(QColor(135,135,135));
                    itemParent->setSelected(true);
                }
            }
        }
    }
    QGraphicsView::mousePressEvent(event);
}

void GraphicsView::updateScene()
{
    int itemsCount = scene->imageCellChain->getCount();
    CellItem *cellItem = 0;

    for(int i=0; i<itemsCount; i++){
        cellItem = scene->imageCellChain->cellItemAt(i);
        if(!scene->items().contains(cellItem))
            scene->addItem(cellItem);
    }
    this->adjustCellItems();
}
