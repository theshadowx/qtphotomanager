#include "confwidget.h"
#include "graphicsview.h"

ConfWidget::ConfWidget(QWidget *parent) :
    QWidget(parent)
{
    brightnessSlider = new QSlider(Qt::Horizontal,this);
    brightnessLabel = new QLabel("Brightness",this);
    contrastSlider = new QSlider(Qt::Horizontal,this);
    contrastLabel = new QLabel("Contrast",this);
    saveButton = new QPushButton("Save",this);
    cancelButton = new QPushButton("Cancel",this);

    brightnessSlider->setGeometry(90, 20, 1250 * 1/6, 20);
    brightnessLabel->setGeometry(5, 20, 80, 20);
    contrastSlider->setGeometry(90, 45, 1250 * 1/6, 20);
    contrastLabel->setGeometry(5, 45, 80, 20);
    saveButton->setGeometry(1250 * 1/16, 750 * 3/4,
                            saveButton->size().width(),saveButton->size().height());
    cancelButton->setGeometry(1250 * 1/16 + saveButton->size().width(), 750 * 3/4,
                            cancelButton->size().width(),cancelButton->size().height());

    brightnessSlider->setMaximum(3);
    brightnessSlider->setMinimum(0);
    brightnessSlider->setSliderPosition(1);

    QObject::connect(cancelButton, SIGNAL(clicked()), this, SLOT(on_cancelButton_clicked()));
    QObject::connect(saveButton, SIGNAL(clicked()), this, SLOT(on_saveButton_clicked()));
    QObject::connect(brightnessSlider, SIGNAL(valueChanged(int)), this, SLOT(brightnessValue()));
    QObject::connect(contrastSlider, SIGNAL(valueChanged(int)), this, SLOT(contrastValue()));

}

void ConfWidget::on_cancelButton_clicked()
{
    brightnessSlider->setValue(1);

    qreal scaleFactor = view->transform().m11();
    view->sceneProcessing->cellItemSelected->image->setPixmap(pixOriginal);
    view->scale(1/scaleFactor,1/scaleFactor);
    view->sceneProcessing->removeItem(view->scene->cellItemSelected->image);
    view->scene->addItem(view->scene->cellItemSelected);
    view->scene->cellItemSelected->image->setParentItem(view->scene->cellItemSelected);
    view->setScene(view->scene);
    view->resize(view->parentWidget()->frameSize().width()*3/4,view->parentWidget()->frameSize().height());

    view->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    view->adjustCellItems();

    emit cancelButton_clicked();
    this->hide();
}

void ConfWidget::on_saveButton_clicked()
{
    brightnessSlider->setValue(1);

    qreal scaleFactor = view->transform().m11();
    view->scale(1/scaleFactor,1/scaleFactor);
    view->sceneProcessing->removeItem(view->scene->cellItemSelected->image);
    view->scene->addItem(view->scene->cellItemSelected);
    view->scene->cellItemSelected->image->setParentItem(view->scene->cellItemSelected);
    view->setScene(view->scene);
    view->resize(view->parentWidget()->frameSize().width()*3/4,view->parentWidget()->frameSize().height());
    view->scene->setSceneRect(view->geometry());
    view->adjustCellItems();

    emit saveButton_clicked();
    this->hide();
}


void ConfWidget::resizeEvent(QResizeEvent*)
{
    saveButton->setGeometry(size().width() * 1/4, size().height() * 3/4,
                            saveButton->size().width(),saveButton->size().height());
    cancelButton->setGeometry(size().width() * 1/4 + saveButton->size().width(), size().height() * 3/4,
                              cancelButton->size().width(),cancelButton->size().height());

}

void ConfWidget::brightnessValue()
{
    #ifdef Q_OS_LINUX
        float alpha = brightnessSlider->value();
        for( int y = 0; y < matProcessed.rows; y++ ){
            for( int x = 0; x < matProcessed.cols; x++ ){
                for( int c = 0; c < 3; c++ ){
                    matProcessed.at<cv::Vec3b>(y,x)[c] =
                            cv::saturate_cast<uchar>( alpha*(matOriginal.at<cv::Vec3b>(y,x)[c] ) + 0 );
                }
            }
        }

        ImageItem *item = static_cast<ImageItem*> (view->sceneProcessing->items().at(0));
        QImage imagetmp(matProcessed.data, matProcessed.cols,matProcessed.rows,QImage::Format_RGB888);
        item->setPixmap(QPixmap::fromImage(imagetmp));
    #endif


}

void ConfWidget::contrastValue()
{

}
