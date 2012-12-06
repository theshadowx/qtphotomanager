#include "graphicsview.h"
#include "confwidget.h"


graphicsView::graphicsView(QWidget *parent)
    : QGraphicsView(parent)
{
    scene = new graphicsScene(this);
    scene->setSceneRect(-300, -300, 600, 600);
    setScene(scene);

    sceneProcessing = new graphicsScene(this);
    sceneProcessing->setSceneRect(-300, -300, 600, 600);

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
    if(this->QGraphicsView::scene()==scene){
        if(scene->itemAt(mapToScene(event->pos()))!=NULL){
            CellItem *item = static_cast<CellItem*> (scene->itemAt(mapToScene(event->pos())));
            if(scene->cellItemList.contains(item)){
                scene->cellItemSelected  = item;
                this->resize(this->size().width()*3/4,this->size().height());
                this->setScene(this->sceneProcessing);
                scene->removeItem(scene->cellItemSelected);
                sceneProcessing->addItem(scene->cellItemSelected->image);
                sceneProcessing->cellItemSelected = scene->cellItemSelected;

                confWidget->resize(confWidget->parentWidget()->frameSize().width()*1/4,confWidget->parentWidget()->frameSize().height());
                confWidget->setGeometry(confWidget->parentWidget()->frameSize().width() * 3/4,0,confWidget->size().width(),confWidget->size().height());
                confWidget->show();
                #ifdef Q_OS_LINUX
                    QString strPath = QDir().currentPath() + "/../../PhotoManager/" + item->getImagePath();
                    confWidget->matOriginal = cv::imread(strPath.toStdString());
                    confWidget->matProcessed = cv::imread(strPath.toStdString());
                #endif
                confWidget->pixOriginal = item->image->pixmap();
                this->fitInView(scene->cellItemSelected->image,Qt::KeepAspectRatio);
            }else{
                CellItem *itemParent = static_cast<CellItem*> (item->parentItem());
                if(scene->cellItemList.contains(itemParent)){
                    scene->cellItemSelected  = itemParent;
                    this->resize(this->size().width()*3/4,this->size().height());
                    this->setScene(this->sceneProcessing);
                    scene->removeItem(scene->cellItemSelected);
                    sceneProcessing->addItem(scene->cellItemSelected->image);
                    sceneProcessing->cellItemSelected = scene->cellItemSelected;

                    confWidget->resize(confWidget->parentWidget()->frameSize().width()*1/4,confWidget->parentWidget()->frameSize().height());
                    confWidget->setGeometry(confWidget->parentWidget()->frameSize().width() * 3/4,0,confWidget->size().width(),confWidget->size().height());
                    confWidget->show();
                    #ifdef Q_OS_LINUX
                        QString strPath = QDir().currentPath() + "/../../PhotoManager/" + itemParent->getImagePath();
                        confWidget->matOriginal = cv::imread(strPath.toStdString());
                        confWidget->matProcessed = cv::imread(strPath.toStdString());
                    #endif

                    confWidget->pixOriginal = itemParent->image->pixmap();
                    this->fitInView(scene->cellItemSelected->image,Qt::KeepAspectRatio);
                }
            }
        }
    }
}

void graphicsView::adjustCellItems()
{
    int itemsCount = scene->cellItemList.count();

    int imageOffsetHeight = 150;
    int imageOffsetWidth = 170;
    int leftMargin = 70;
    int topMargin = 40;
    int bottomMargin = 40;
    int columnCount =(int) (this->parentWidget()->frameSize().width()-leftMargin)/(imageOffsetWidth+leftMargin)+1;

    for(int i = 0; i < itemsCount; i++) {
        int columnOffset = (37 * (i % columnCount));
        int x = ((i % columnCount) * imageOffsetWidth) + leftMargin + columnOffset;
        int y = ((i / columnCount) * (imageOffsetHeight + bottomMargin)) + topMargin;

        scene->cellItemList.at(i)->setPos(this->mapToScene(x, y));
    }
}
