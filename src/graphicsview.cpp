#include "graphicsview.h"
#include <math.h>

/// Constructor of GraphicsView
GraphicsView::GraphicsView(QWidget *parent)
    : QGraphicsView(parent)
{
    scene = new GraphicsScene(this);
    scene->setSceneRect(-300, -300, 600, 600);
    setScene(scene);

    sceneProcessing = new GraphicsScene(this);
    sceneProcessing->setSceneRect(-300, -300, 600, 600);
    sceneProcessing->setBackgroundBrush(QBrush(QColor().black()));

    ctrlClicked = false;
    ctrlToggled = false;
    cellItemSelected = 0;

    this->setContextMenuPolicy(Qt::CustomContextMenu);
}

GraphicsView::~GraphicsView()
{
}

void GraphicsView::setupProcessingMode(CellItem *cellItem)
{
    cellItemSelected  = cellItem;

    this->setScene(sceneProcessing);
    scene->removeItem(cellItemSelected);

    qreal scaleFactor = this->transform().m11();
    this->scale(1/scaleFactor,1/scaleFactor);

    sceneProcessing->setSceneRect(0,0,cellItemSelected->image->pixmap().width(),cellItemSelected->image->pixmap().height());
    cellItemSelected->image->adjust(cellItemSelected->image->pixmap().width(),cellItemSelected->image->pixmap().height());
    sceneProcessing->addItem(cellItemSelected->image);

    if(cellItemSelected->image->pixmap().height() >= this->height() ||
            cellItemSelected->image->pixmap().width() >= this->width()){
        this->fitInView(cellItemSelected->image, Qt::KeepAspectRatio);
    }else{
        qreal scaleFactor = this->transform().m11();
        this->scale(1/scaleFactor,1/scaleFactor);
        QPointF pos = this->mapToScene(this->geometry().center().x() - cellItemSelected->image->pixmap().width()/2,
                              this->geometry().center().y()- cellItemSelected->image->pixmap().height()/2);
        cellItemSelected->image->setPos(pos);
    }

    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    emit cellItemClicked(cellItem);
}

void GraphicsView::setupGlobalMode()
{
    qreal scaleFactor = this->transform().m11();
    this->scale(1/scaleFactor,1/scaleFactor);
    if(cellItemSelected){
        cellItemSelected->image->adjust();
        cellItemSelected->setColor(QColor(255,255,255));
        if(sceneProcessing->items().contains(cellItemSelected->image))
            sceneProcessing->removeItem(cellItemSelected->image);
        cellItemSelected->image->setParentItem(cellItemSelected);
    }
    this->setScene(scene);

    cellItemSelected = 0;

    this->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    for(int i=0;i<imageCellChain->getCount();i++){
        if(!scene->items().contains(imageCellChain->cellItemAt(i)))
            scene->addItem(imageCellChain->cellItemAt(i));
    }

    this->adjustCellItems();
    this->show();
}


/// Ajust the CellItems in the View
void GraphicsView::adjustCellItems()
{
    int x = 0;
    int y = 0;
    int itemsCount = 0;
    int imageOffsetHeight = 150;
    int imageOffsetWidth = 170;
    int leftMargin = 35;
    int rightMargin = 35;
    int topMargin = 20;
    int bottomMargin = 20;
    int columnCount = 0;
    int lineCount = 0;
    int rectHeight = 0;
    int imageSlotWidth = 0;
    float limitRatioMargin = 0.0;


    QList<CellItem*> cellList;

    for(int i=0;i<imageCellChain->getCount();i++){
        if(scene->items().contains(imageCellChain->cellItemAt(i)))
            cellList.append(imageCellChain->cellItemAt(i));
    }
//    for(int i=0;i<scene->items().length();i++){
//        if(imageCellChain->contains(static_cast<CellItem*>(scene->items().at(i))))
//            cellList.append(static_cast<CellItem*>(scene->items().at(i)));
//    }

    /// Number of items
    itemsCount = cellList.length();

    /// Calculate the number of column and lines needed
    imageSlotWidth = rightMargin + imageOffsetWidth + leftMargin;
    limitRatioMargin = (float)(rightMargin + imageOffsetWidth)/(imageSlotWidth);
    columnCount = floor(((float)(this->frameSize().width())/imageSlotWidth));
    if(fmod(((float)(this->frameSize().width())/imageSlotWidth),columnCount)>limitRatioMargin)
        columnCount++;
    lineCount = ceil((float)itemsCount/columnCount);

    /// Setup the scene boundary
    rectHeight = lineCount *(topMargin + bottomMargin + imageOffsetHeight) + 3*bottomMargin;
    scene->setSceneRect(mapFromGlobal(QPoint(0,0)).x(),
                        mapFromGlobal(QPoint(0,0)).y(),
                        columnCount * (rightMargin+imageOffsetWidth+leftMargin)-rightMargin,
                        rectHeight);

    /// Positionning the cellItems
    this->verticalScrollBar()->setValue(this->verticalScrollBar()->minimum());
    for(int j = 0; j < lineCount; j++) {
        for(int i = 0; i < columnCount; i++) {
            if(j*columnCount+i >= itemsCount){
                continue;
            }else{
                x = i*(leftMargin + imageOffsetWidth + rightMargin) + leftMargin;
                y = j*(topMargin + imageOffsetHeight + bottomMargin)+ topMargin;
                cellList.at(j*columnCount+i)->setPos(this->mapToScene(x, y));
            }
        }
    }
    cellList.clear();
}

/// update global scene from imageCellChain
void GraphicsView::updateScene()
{
    int itemsCount = imageCellChain->getCount();
    CellItem *cellItem = 0;

    for(int i=0; i<itemsCount; i++){
        cellItem = imageCellChain->cellItemAt(i);
        if(!scene->items().contains(cellItem))
            scene->addItem(cellItem);
    }
    this->adjustCellItems();
}


/// Mouse double click event callback
void GraphicsView::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        if(currentUser->getPermission() == Users::LEVEL_1){
            if(this->QGraphicsView::scene() == this->scene){
                CellItem *item = static_cast<CellItem*> (this->scene->itemAt(this->mapToScene(event->pos())));
                if(item!=NULL){
                    if(imageCellChain->contains(item)){
                        this->setupProcessingMode(item);
                    }else{
                        CellItem *itemParent = static_cast<CellItem*> (item->parentItem());
                        this->setupProcessingMode(itemParent);
                    }
                }
            }
        }
    }
    QGraphicsView::mouseDoubleClickEvent(event);
}

/// Mouse press event callback
void GraphicsView::mousePressEvent(QMouseEvent *event)
{
    if(!this->isHidden()){
        if(this->QGraphicsView::scene() == scene){
            if(event->button() == Qt::LeftButton){
                CellItem *clickedItem = static_cast<CellItem*> (scene->itemAt(this->mapToScene(event->pos())));
                if(clickedItem!=NULL){
                    /// Item was clicked
                    if(!ctrlClicked){
                        selectedCellItemsList.clear();
                        if(cellItemSelected){
                            cellItemSelected->setColor(QColor(255,255,255));
                            cellItemSelected = 0;
                        }
                        if(imageCellChain->contains(clickedItem)){
                            selectedCellItemsList.append(clickedItem);
                            cellItemSelected = clickedItem;
                            clickedItem->setColor(QColor(176, 189, 201, 255));
                        }else{
                            CellItem *itemParent = static_cast<CellItem*> (clickedItem->parentItem());
                            selectedCellItemsList.append(itemParent);
                            cellItemSelected = itemParent;
                            itemParent->setColor(QColor(176, 189, 201, 255));
                        }
                    /// Item was clicked with control key pressed
                    }else{
                        if(imageCellChain->contains(clickedItem)){
                            cellItemSelected = clickedItem;
                            selectedCellItemsList.append(clickedItem);
                            clickedItem->setColor(QColor(176, 189, 201));
                        }else{
                            CellItem *itemParent = static_cast<CellItem*> (clickedItem->parentItem());
                            selectedCellItemsList.append(itemParent);
                            cellItemSelected = itemParent;
                            itemParent->setColor(QColor(176, 189, 201));
                        }
                    }
                /// Blank area was clicked with control key pressed
                }else if(ctrlClicked){

                /// Blank area was clicked
                }else{
                    for(int i=0; i<selectedCellItemsList.length();i++){
                        CellItem* cellItem = selectedCellItemsList.at(i);
                        cellItem->setColor(QColor(255,255,255));
                    }
                    cellItemSelected = 0;
                    selectedCellItemsList.clear();
                }
                scene->update();
            }
        }
    }
    QGraphicsView::mousePressEvent(event);
}

/// Wheel event callback
void GraphicsView::wheelEvent(QWheelEvent* event)
{
    if(!this->isHidden()){
        if(this->QGraphicsView::scene() == sceneProcessing){
            this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
            ctrlToggled = false;

            double scaleFactor = 1.15;

            if(event->delta() > 0) {
                /// Zoom in
                this->scale(scaleFactor, scaleFactor);
            }else {
                /// Zooming out
                this->scale(1.0 / scaleFactor, 1.0 / scaleFactor);
            }
        }else if(this->QGraphicsView::scene() == scene){
            int sliderPos = this->verticalScrollBar()->sliderPosition();
            if(event->delta() > 0) {
                this->verticalScrollBar()->setSliderPosition(sliderPos-50);
            }else {
                this->verticalScrollBar()->setSliderPosition(sliderPos+50);
            }

        }
    }
    QGraphicsView::wheelEvent(event);
}

/// Key pressed event callback
void GraphicsView::keyPressEvent(QKeyEvent *event)
{
    if(!this->isHidden()){
        if(this->QGraphicsView::scene() == scene){
            QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
            CellItem* cellItem = 0;

            switch (keyEvent->key()) {
                case Qt::Key_Delete:
                    ctrlToggled = false;
                    if(!selectedCellItemsList.empty()){
                        cellItemSelected = 0;

                        emit cellItemDeleted(selectedCellItemsList);

                        for(int i=0; i<selectedCellItemsList.length();i++){
                            cellItem = selectedCellItemsList.at(i);
                            imageCellChain->deleteCellItem(cellItem);
                         }
                        selectedCellItemsList.clear();
                        this->adjustCellItems();
                    }
                    break;

                case Qt::Key_A:
                    selectedCellItemsList.clear();
                    if(ctrlToggled){
                        cellItemSelected = 0;
                        for(int i=0; i<imageCellChain->getCount();i++){
                            CellItem *cellItem = imageCellChain->cellItemAt(i);
                            cellItem->setColor(QColor(176, 189, 201));
                            selectedCellItemsList.append(cellItem);
                        }
                    }else{
                        for(int i=0; i<selectedCellItemsList.length();i++){
                            cellItem = selectedCellItemsList.at(i);
                            cellItem->setColor(QColor(255, 255, 255));
                        }
                    }
                    ctrlToggled = false;
                    break;

                case Qt::Key_Control:
                    ctrlClicked = true;
                    ctrlToggled = true;
                    break;

                default:
                    ctrlToggled = false;
                    for(int i=0; i<selectedCellItemsList.length();i++){
                        cellItem = selectedCellItemsList.at(i);
                        cellItem->setColor(QColor(255, 255, 255));
                    }
                    selectedCellItemsList.clear();
                    this->QGraphicsView::keyPressEvent(event);
                    break;
            }
            scene->update();
        }
    }
}

/// Release key event callback
void GraphicsView::keyReleaseEvent(QKeyEvent *event)
{
    if(this->QGraphicsView::scene() == scene){
        switch (event->key()) {
            case Qt::Key_Control:
                    ctrlClicked = false;
                break;
            default:
                QFrame::keyPressEvent(event);
        }
    }
}

/// Resize window event callBack
void GraphicsView::resizeEvent(QResizeEvent *)
{
    if(!this->isHidden()){
        if(this->QGraphicsView::scene() == scene){
            this->verticalScrollBar()->setValue(this->verticalScrollBar()->minimum());
            this->adjustCellItems();
        }else if(this->QGraphicsView::scene() == sceneProcessing){
            if(cellItemSelected->image->pixmap().height() >= this->height() ||
                    cellItemSelected->image->pixmap().width() >= this->width()){
                this->fitInView(cellItemSelected->image, Qt::KeepAspectRatio);
            }else{
                qreal scaleFactor = this->transform().m11();
                this->scale(1/scaleFactor,1/scaleFactor);
                QPointF pos = this->mapToScene(this->geometry().center().x() - cellItemSelected->image->pixmap().width()/2,
                                      this->geometry().center().y()- cellItemSelected->image->pixmap().height()/2);
                cellItemSelected->image->setPos(pos);

            }
        }
    }
}
