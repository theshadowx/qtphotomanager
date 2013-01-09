#include "confwidget.h"
#include "graphicsview.h"

/// Constructor of ConfWidget
ConfWidget::ConfWidget(QWidget *parent) :
    QWidget(parent)
{
    histView = new QGraphicsView(this);
    histPixmap = new QGraphicsPixmapItem();
    brightnessSlider = new QSlider(Qt::Horizontal,this);
    brightnessLabel = new QLabel("Brightness",this);
    contrastSlider = new QSlider(Qt::Horizontal,this);
    contrastLabel = new QLabel("Contrast",this);
    layout = new QHBoxLayout(this);
    saveButton = new QPushButton("Save",this);
    cancelButton = new QPushButton("Cancel",this);
    leftSpacer = new QSpacerItem(50,20,QSizePolicy::Expanding);
    rightSpacer = new QSpacerItem(50,20,QSizePolicy::Expanding);

    layout->addSpacerItem(leftSpacer);
    layout->addWidget(saveButton);
    layout->addWidget(cancelButton);
    layout->addSpacerItem(rightSpacer);

    QGraphicsScene *scene = new QGraphicsScene(histView);

    histView->setGeometry(5,20,1250 * 1/4-10,200);
    brightnessSlider->setGeometry(90, 220, 1250 * 1/6, 20);
    brightnessLabel->setGeometry(5, 220, 80, 20);
    contrastSlider->setGeometry(90, 245, 1250 * 1/6, 20);
    contrastLabel->setGeometry(5, 245, 80, 20);

    histView->setScene(scene);
    histView->scene()->addItem(histPixmap);
    histPixmap->setPos(histView->mapToScene(0, 0));

    brightnessSlider->setMaximum(100);
    brightnessSlider->setMinimum(-100);
    brightnessSlider->setTickInterval(1);
    brightnessSlider->setValue(0);
    brightnessSlider->setTickPosition(QSlider::TicksBelow);

    contrastSlider->setMaximum(90);
    contrastSlider->setMinimum(1);
    contrastSlider->setTickInterval(1);
    contrastSlider->setValue(30);
    contrastSlider->setTickPosition(QSlider::TicksBelow);


    QObject::connect(cancelButton, SIGNAL(clicked()), this, SLOT(on_cancelButton_clicked()));
    QObject::connect(saveButton, SIGNAL(clicked()), this, SLOT(on_saveButton_clicked()));
    QObject::connect(brightnessSlider, SIGNAL(valueChanged(int)), this, SLOT(brightnessContrast()));
    QObject::connect(contrastSlider, SIGNAL(valueChanged(int)), this, SLOT(brightnessContrast()));

}

/// Destructor of the widget
ConfWidget::~ConfWidget()
{
}

/// Brightness and contrast callback
void ConfWidget::brightnessContrast()
{
    float alpha = ((float) contrastSlider->value())/30;
    float beta = brightnessSlider->value();

    if(!view->sceneProcessing->items().isEmpty()){
        for( int y = 0; y < matProcessed.rows; y++ ){
            for( int x = 0; x < matProcessed.cols; x++ ){
                for( int c = 0; c < 3; c++ ){
                    matProcessed.at<cv::Vec3b>(y,x)[c] =
                            cv::saturate_cast<uchar>( alpha*(matOriginal.at<cv::Vec3b>(y,x)[c] ) + beta );
                }
            }
        }

        ImageItem *item = static_cast<ImageItem*> (view->sceneProcessing->items().at(0));
        cv::Mat matProcessedRGB( matProcessed.rows, matProcessed.cols, CV_8UC3, cv::Scalar( 255,255,255) );

        cv::cvtColor(matProcessed, matProcessedRGB, CV_BGR2RGB);
        QImage imagetmp(matProcessedRGB.data, matProcessedRGB.cols,matProcessedRGB.rows,matProcessedRGB.step,QImage::Format_RGB888);
        item->setPixmap(QPixmap::fromImage(imagetmp));

        this->showHistogram();
    }

}

/// Calculate the histogram of the image
void ConfWidget::showHistogram()
{
    /// Separate the image in 3 places ( B, G and R )
    cv::vector<cv::Mat> bgr_planes;
    cv::split(matProcessed, bgr_planes);

    /// Establish the number of bins
    int histSize = 256;

    /// Set the ranges (for B,G,R))
    float range[] = { 0, 256 } ;
    const float *histRange = { range };

    bool uniform = true;
    bool accumulate = false;

    cv::Mat b_hist;
    cv::Mat g_hist;
    cv::Mat r_hist;

    /// Compute the histograms:
    cv::calcHist(&bgr_planes[0], 1, 0, cv::Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);
    cv::calcHist(&bgr_planes[1], 1, 0, cv::Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
    cv::calcHist(&bgr_planes[2], 1, 0, cv::Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);

    /// Draw the histograms for B, G and R
    int hist_w = histView->size().width();
    int hist_h = histView->size().height();
    int bin_w = cvRound((double) hist_w/histSize );

    cv::Mat histImage( hist_h, hist_w, CV_8UC3, cv::Scalar( 255,255,255) );

    /// Normalize the result to [ 0, histImage.rows ]
    cv::normalize(b_hist, b_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat() );
    cv::normalize(g_hist, g_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat() );
    cv::normalize(r_hist, r_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat() );

    /// Draw for each channel
    for( int i = 1; i < histSize; i++ )
    {
        cv::line( histImage, cv::Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1))) ,
                  cv::Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ),
                  cv::Scalar(255, 0, 0), 2, 8, 0);
        cv::line( histImage, cv::Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1))) ,
                  cv::Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ),
                  cv::Scalar( 0, 255, 0), 2, 8, 0);
        cv::line( histImage, cv::Point( bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1))) ,
                  cv::Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(i)) ),
                  cv::Scalar( 0, 0, 255), 2, 8, 0);
    }

    QImage imageTmp(histImage.data, histImage.cols,histImage.rows,histImage.step,QImage::Format_RGB666);
    histPixmap->setPixmap(QPixmap().fromImage(imageTmp));
    histPixmap->setPos(histView->mapToScene(0, 0));
    histView->fitInView(histPixmap,Qt::KeepAspectRatio);
}

/// Cancel button pressed callback
void ConfWidget::on_cancelButton_clicked()
{

    qreal scaleFactor = view->transform().m11();
    view->sceneProcessing->cellItemSelected->image->setPixmap(pixOriginal);
    view->scale(1/scaleFactor,1/scaleFactor);
    view->sceneProcessing->removeItem(view->scene->cellItemSelected->image);
    view->scene->addItem(view->scene->cellItemSelected);
    view->scene->cellItemSelected->image->setParentItem(view->scene->cellItemSelected);
    view->setScene(view->scene);
    view->resize(view->parentWidget()->frameSize().width()*3/4,view->parentWidget()->frameSize().height());

    view->sceneProcessing->cellItemSelected = 0;
    view->scene->cellItemSelected = 0;

    view->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    view->adjustCellItems();

    emit cancelButtonClicked();
    this->hide();

    brightnessSlider->setValue(0);
    contrastSlider->setValue(30);
}

/// Save button pressed callback
void ConfWidget::on_saveButton_clicked()
{
    qreal scaleFactor = view->transform().m11();

    view->scale(1/scaleFactor,1/scaleFactor);
    view->sceneProcessing->removeItem(view->scene->cellItemSelected->image);
    view->scene->addItem(view->scene->cellItemSelected);
    view->scene->cellItemSelected->image->setParentItem(view->scene->cellItemSelected);
    view->setScene(view->scene);
    view->resize(view->parentWidget()->frameSize().width()*3/4,view->parentWidget()->frameSize().height());

    view->sceneProcessing->cellItemSelected = 0;
    view->scene->cellItemSelected = 0;

    view->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    view->adjustCellItems();

    emit saveButtonClicked();
    this->hide();

    brightnessSlider->setValue(0);
    contrastSlider->setValue(30);
}

/// Resize event callback
void ConfWidget::resizeEvent(QResizeEvent*)
{
    histView->setGeometry(5,20,this->parentWidget()->frameSize().width()*1/4 - 10,200);
    histView->setSceneRect(histView->geometry());
    histPixmap->setPos(histView->mapToScene(0, 0));

    brightnessSlider->setGeometry(90, 220, this->parentWidget()->frameSize().width() * 1/6, 20);
    brightnessLabel->setGeometry(5, 220, 80, 20);
    contrastSlider->setGeometry(90, 245, this->parentWidget()->frameSize().width() * 1/6, 20);
    contrastLabel->setGeometry(5, 245, 80, 20);

    bool sceneEmpty =  (view->sceneProcessing->items().isEmpty());
    if(!sceneEmpty){
        this->showHistogram();
    }
}

/// Paint event callBack
void ConfWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
