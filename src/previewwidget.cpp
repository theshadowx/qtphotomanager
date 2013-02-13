#include "previewwidget.h"
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QGraphicsSceneWheelEvent>

/// Constructor
PreviewWidget::PreviewWidget(QWidget *parent) :
    QWidget(parent)
{
    cellItemSelected = 0;
    imageCellChain = 0;

    /// ****** init UI ***** ///
    buttonBox = new QDialogButtonBox(Qt::Horizontal,this);
    buttonBox->addButton(QDialogButtonBox::Close);

    mainView = new QGraphicsView(this);
    QGraphicsScene *mainScene = new QGraphicsScene(this);
    mainView->setScene(mainScene);

    listView = new QGraphicsView(this);
    QGraphicsScene *listScene = new QGraphicsScene(this);
    listView->setScene(listScene);
    listView->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    listView->setMinimumHeight(150);
    listView->scene()->installEventFilter(this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(buttonBox);
    layout->addWidget(mainView);
    layout->addWidget(listView);

    frame = new QFrame(this);
    frame->setLayout(layout);

    /// *************** Connection SLOT/SIGNAL ***************** ///
    QObject::connect(buttonBox, SIGNAL(clicked(QAbstractButton*)), this , SLOT(onButtonClicked(QAbstractButton*)));
}

/// Destructor
PreviewWidget::~PreviewWidget()
{
}

/// Adjust cellItems in the listView
void PreviewWidget::adjustCellItems()
{
    int x = 0;
    int y = 0;
    int itemsCount = 0;
    int imageOffsetWidth = 170;
    int imageOffsetHeight = 120;
    int leftMargin = 35;
    int rightMargin = 35;
    int topMargin = (listView->frameSize().height() - imageOffsetHeight - 20)/2;
    int rectWidth = 0;

    itemsCount = imageCellChain->getCount();
    rectWidth =  itemsCount * (leftMargin + rightMargin + imageOffsetWidth);
    listView->scene()->setSceneRect(0,
                                    0,
                                    rectWidth,
                                    listView->frameSize().height()-20);

    for(int i = 0; i < itemsCount; i++) {
        x = i*(leftMargin + imageOffsetWidth + rightMargin) + leftMargin;
        y = topMargin;

        imageCellChain->cellItemAt(i)->setPos(x,y);
        listView->scene()->addItem(imageCellChain->cellItemAt(i));
    }
}

/// Show Image in the main view
void PreviewWidget::showImage(CellItem *cellItem)
{
    ImageItem *imageItem = 0;
    imageItem = new ImageItem(cellItem->image->pixmap());
    mainView->scene()->addItem(imageItem);
    mainView->scene()->setSceneRect(0,0,imageItem->pixmap().width(),imageItem->pixmap().height());
    imageItem->adjust(imageItem->pixmap().width(),imageItem->pixmap().height());

    if(imageItem->pixmap().height() >= mainView->height() ||
            imageItem->pixmap().width() >= mainView->width()){

        mainView->fitInView(imageItem, Qt::KeepAspectRatio);
    }else{
        qreal scaleFactor = mainView->transform().m11();
        mainView->scale(1/scaleFactor,1/scaleFactor);
        QPointF pos = mainView->mapToScene(this->geometry().center().x() - imageItem->pixmap().width()/2,
                              mainView->geometry().center().y() - imageItem->pixmap().height()/2);
        imageItem->setPos(pos);
    }
}

/// Resize event callback
void PreviewWidget::resizeEvent(QResizeEvent *)
{
    frame->resize(this->frameSize().width(), this->frameSize().height());
    if(!mainView->scene()->items().empty()){
        ImageItem *imageItem = static_cast<ImageItem*>(mainView->scene()->items().at(0));
        if(imageItem->pixmap().height() >= mainView->height() ||
                imageItem->pixmap().width() >= mainView->width()){

            mainView->fitInView(imageItem, Qt::KeepAspectRatio);
        }else{
            qreal scaleFactor = mainView->transform().m11();
            mainView->scale(1/scaleFactor,1/scaleFactor);
            QPointF pos = mainView->mapToScene(this->geometry().center().x() - imageItem->pixmap().width()/2,
                                  mainView->geometry().center().y() - imageItem->pixmap().height()/2);
            imageItem->setPos(pos);
        }
    }
}

/// Event filter for listView's scene
bool PreviewWidget::eventFilter(QObject *obj, QEvent *event)
{
    CellItem *clickedItem = static_cast<CellItem*> (listView->scene()->mouseGrabberItem());
    if(event->type() == QEvent::GraphicsSceneMouseRelease){
        if(clickedItem != NULL){
            if(!mainView->scene()->items().empty())
                mainView->scene()->clear();
            if(!imageCellChain->contains(clickedItem)){
                clickedItem =static_cast<CellItem*>(clickedItem->parentItem());
            }
            cellItemSelected = clickedItem;
            this->showImage(cellItemSelected);
        }
    }else if(event->type() == QEvent::GraphicsSceneWheel){
        QGraphicsSceneWheelEvent  *wheelMouseEvent = static_cast<QGraphicsSceneWheelEvent*>(event);;
        int sliderPos = listView->horizontalScrollBar()->sliderPosition();
        if(wheelMouseEvent->delta() > 0) {
            listView->horizontalScrollBar()->setSliderPosition(sliderPos-50);
        }else {
            listView->horizontalScrollBar()->setSliderPosition(sliderPos+50);
        }
    }
    return QWidget::eventFilter(obj, event);
}

/// Close button callback
void PreviewWidget::onButtonClicked(QAbstractButton *button)
{
    if(buttonBox->buttonRole(button) == QDialogButtonBox::RejectRole){
        this->hide();
        if(!mainView->scene()->items().empty())
            mainView->scene()->clear();
        emit cancelButtonClicked();
    }
}
