#include "confwidget.h"
#include "graphicsview.h"
#include "filterkerneldialog.h"

/// Constructor of ConfWidget
ConfWidget::ConfWidget(QWidget *parent) :
    QWidget(parent)
{
    /// *************** init interface ***************** ///

    /// ****** Histogram ****** ///
    histLabel = new QLabel("Histogram",this);
    histLabel->setFont(QFont(QFont().defaultFamily(),12,QFont::Bold));

    histogramButtonGroup = new QButtonGroup(this);
    colorRadioButton = new QRadioButton("Color",this);
    grayscaleRadioButton = new QRadioButton("GrayScale",this);

    histogramButtonGroup->addButton(grayscaleRadioButton,0);
    histogramButtonGroup->addButton(colorRadioButton,1);
    histogramButtonGroup->setExclusive(true);
    histogramButtonGroup->button(0)->setChecked(true);

    histView = new QGraphicsView(this);
    histView->setObjectName("histView");
    QGraphicsScene *scene = new QGraphicsScene(histView);
    histView->setScene(scene);
    histView->setFrameShape(QFrame::NoFrame);

    histogram = new Histogram;
    histView->scene()->addItem(histogram);

    /// ****** Brightness ****** ///
    brightnessLabel = new QLabel("Brightness",this);
    brightnessSlider = new QSlider(Qt::Horizontal,this);
    brightnessSpinBox = new QSpinBox(this);

    brightnessLabel->setFont(QFont(QFont().defaultFamily(),11,QFont::Bold));
    brightnessSlider->setMaximum(256);
    brightnessSlider->setMinimum(-256);
    brightnessSlider->setTickInterval(1);
    brightnessSlider->setValue(0);
    brightnessSlider->setTickPosition(QSlider::TicksBelow);
    brightnessSpinBox->setMinimum(-256);
    brightnessSpinBox->setMaximum(256);
    brightnessSpinBox->setValue(0);

    /// ****** Contrast ****** ///
    contrastLabel = new QLabel("Contrast",this);
    contrastSlider = new QSlider(Qt::Horizontal,this);
    contrastSpinBox = new QDoubleSpinBox(this);

    contrastLabel->setFont(QFont(QFont().defaultFamily(),11,QFont::Bold));
    contrastSlider->setMaximum(255);
    contrastSlider->setMinimum(0);
    contrastSlider->setTickInterval(3);
    contrastSlider->setValue(30);
    contrastSlider->setTickPosition(QSlider::TicksBelow);
    contrastSpinBox->setMinimum(0);
    contrastSpinBox->setMaximum(255/30.0);
    contrastSpinBox->setValue(1);

    /// ****** Save and Cancel Buttons ****** ///
    saveCancelFrame = new QFrame(this);
    saveCancelLayout = new QHBoxLayout(saveCancelFrame);
    saveButton = new QPushButton("Save",saveCancelFrame);
    cancelButton = new QPushButton("Cancel",saveCancelFrame);
    leftSpacer = new QSpacerItem(50,20,QSizePolicy::Expanding);
    rightSpacer = new QSpacerItem(50,20,QSizePolicy::Expanding);

    saveCancelLayout->addSpacerItem(leftSpacer);
    saveCancelLayout->addWidget(saveButton);
    saveCancelLayout->addWidget(cancelButton);
    saveCancelLayout->addSpacerItem(rightSpacer);

    /// *********** Filters ******************** ///
    filterFrame = new QFrame(this);
    filterHLayout = new QHBoxLayout;
    filterVLayout = new QVBoxLayout;
    filterLeftSpacer = new QSpacerItem(50,20,QSizePolicy::Expanding);
    filterRightSpacer = new QSpacerItem(50,20,QSizePolicy::Expanding);
    filterGroupButton = new QButtonGroup(filterFrame);
    filterButtonMean = new QPushButton("Mean Filter",filterFrame);
    filterButtonSharpness = new QPushButton("Sharpness Filter",filterFrame);
    filterButtonLaplacian = new QPushButton("Laplacian Filter",filterFrame);
    filterButtonEdge = new QPushButton("Edge Filter",filterFrame);
    customFilterButton = new QPushButton("Setup a Filter...",filterFrame);
    originalFilterButton = new QPushButton("Original Image",filterFrame);

    filterVLayout->addWidget(filterButtonMean);
    filterVLayout->addWidget(filterButtonSharpness);
    filterVLayout->addWidget(filterButtonLaplacian);
    filterVLayout->addWidget(filterButtonEdge);
    filterVLayout->addWidget(customFilterButton);
    filterVLayout->addWidget(originalFilterButton);

    filterHLayout->addSpacerItem(filterLeftSpacer);
    filterHLayout->addLayout(filterVLayout);
    filterHLayout->addSpacerItem(filterRightSpacer);

    filterGroupButton->addButton(filterButtonMean,0);
    filterGroupButton->addButton(filterButtonSharpness,1);
    filterGroupButton->addButton(filterButtonLaplacian,2);
    filterGroupButton->addButton(filterButtonEdge,3);
    filterGroupButton->addButton(customFilterButton,4);
    filterGroupButton->addButton(originalFilterButton,5);

    filterFrame->setLayout(filterHLayout);

    /// ******** Signals/Slots ************ ///
    QObject::connect(cancelButton, SIGNAL(clicked()), this, SLOT(onCancelButtonClicked()));
    QObject::connect(saveButton, SIGNAL(clicked()), this, SLOT(onSaveButtonClicked()));
    QObject::connect(brightnessSlider, SIGNAL(valueChanged(int)), this, SLOT(brightnessContrast()));
    QObject::connect(brightnessSpinBox, SIGNAL(valueChanged(int)), this, SLOT(brightnessContrast()));
    QObject::connect(contrastSlider, SIGNAL(valueChanged(int)), this, SLOT(brightnessContrast()));
    QObject::connect(contrastSpinBox, SIGNAL(valueChanged(double)), this, SLOT(brightnessContrast()));
    QObject::connect(histogramButtonGroup, SIGNAL(buttonClicked(int)), this, SLOT(drawHistogram(int)));
    QObject::connect(filterGroupButton, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(filter(QAbstractButton*)));

}

/// Destructor of the widget
ConfWidget::~ConfWidget()
{
}

/// Brightness and contrast callback
void ConfWidget::brightnessContrast()
{

    float alpha = 0.0;
    float beta = 0.0;
                                                    /// signal senders
    if(this->sender() == contrastSpinBox){          /// contrastSpinBox
        contrastSlider->blockSignals(true);
        contrastSlider->setValue(contrastSpinBox->value()*30);
        contrastSlider->blockSignals(false);
    }else if(this->sender() == contrastSlider){     /// contrastSlider
        contrastSpinBox->blockSignals(true);
        contrastSpinBox->setValue(contrastSlider->value()/30.0);
        contrastSpinBox->blockSignals(false);
    }else if(this->sender() == brightnessSpinBox){  /// brightnessSpinBox
        brightnessSlider->blockSignals(true);
        brightnessSlider->setValue(brightnessSpinBox->value());
        brightnessSlider->blockSignals(false);
    }else if(this->sender() == brightnessSlider){   /// brightnessSlider
        brightnessSpinBox->blockSignals(true);
        brightnessSpinBox->setValue(brightnessSlider->value());
        brightnessSpinBox->blockSignals(false);
    }
    alpha = ((float) contrastSlider->value()/30.0);
    beta = brightnessSlider->value();

    if(!view->sceneProcessing->items().isEmpty()){
        matOriginal.convertTo(matProcessed, -1, alpha, beta);
        cv::cvtColor(matProcessed, matProcessed, CV_BGR2RGB);
        QImage imagetmp(matProcessed.data, matProcessed.cols,matProcessed.rows,matProcessed.step,QImage::Format_RGB888);
        view->cellItemSelected->image->setPixmap(QPixmap::fromImage(imagetmp));
        histogram->setSrcImage(imagetmp);
        histView->scene()->update();
     }
}

/// Draw the histogram of the image
void ConfWidget::drawHistogram(int type)
{
    histogram->setHistType((Histogram::TYPE) type);
    histogram->setSrcImage(view->cellItemSelected->image->pixmap().toImage());
    histView->scene()->update();
}

/// Filtering
void ConfWidget::filter(QAbstractButton* button)
{

    brightnessSlider->setValue(0);
    contrastSlider->setValue(30);

    /// Declare variables
    cv::Mat kernel;
    int ddepth;

    cv::Point anchor;

    /// Initialize arguments for the filter
    anchor = cv::Point( -1, -1 );
    ddepth = -1;

    double mean[3][3] = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
    double sharpness[3][3] = {{-1, -1, -1}, {-1, 9, -1}, {-1, -1, -1}};
    double laplacian[3][3] = {{0, 1, 0}, {1, -4, 1}, {0, 1, 0}};
    double edge[3][3] = {{-1, -1, -1}, {-1, 8, -1}, {-1, -1, -1}};

    /// Filter's Kernel
    if (button == filterButtonMean){
        kernel = cv::Mat(3,3, CV_64FC1, mean)/ (float)(3*3);
        cv::normalize(kernel, kernel, 1.0, 0.0, CV_L1);
    }else if (button == filterButtonSharpness){
        kernel = cv::Mat(3,3, CV_64FC1, sharpness)/ (float)(3*3);
        cv::normalize(kernel, kernel, 10.0, 0.0, CV_L2);
    }else if (button == filterButtonLaplacian){
        kernel = cv::Mat(3,3, CV_64FC1, laplacian)/ (float)(3*3);
        cv::normalize(kernel, kernel, 5.0, 0.0, CV_L2);
    }else if (button == filterButtonEdge){
        kernel = cv::Mat(3,3, CV_64FC1, edge)/ (float)(3*3);
        cv::normalize(kernel, kernel, 5.0, 0.0, CV_L2);
    }else if(button == customFilterButton){
        FilterKernelDialog filterKernelDialog;
        if(filterKernelDialog.exec()){
            kernel = cv::Mat(3,3, CV_64F, filterKernelDialog.kernelMat)/ (float)(3*3);
            double max = 0;
            for(int i=0; i<3; i++){
                for(int j=0;j<3; j++){
                    if(abs(filterKernelDialog.kernelMat[i][j])>max)
                        max = filterKernelDialog.kernelMat[i][j];
                }
            }
            cv::normalize(kernel, kernel, max, 0.0, CV_L2);
        }else{
            return;
        }
    }

    if(button != originalFilterButton){
    /// Apply filter
        cv::filter2D(matOriginal, matProcessed, ddepth , kernel, anchor, 0, cv::BORDER_REPLICATE );

        /// Conversion from OpenCv data to Qt pixmap data
        cv::cvtColor(matProcessed, matProcessed, CV_BGR2RGB);
        QImage imagetmp(matProcessed.data, matProcessed.cols,matProcessed.rows,matProcessed.step,QImage::Format_RGB888);
        view->cellItemSelected->image->setPixmap(QPixmap::fromImage(imagetmp));
        histogram->setSrcImage(imagetmp);
        histView->scene()->update();
    }else{
        view->cellItemSelected->image->setPixmap(pixOriginal);
        histogram->setSrcImage(pixOriginal.toImage());
        histView->scene()->update();
    }
}

/// Cancel button pressed callback
void ConfWidget::onCancelButtonClicked()
{
    view->cellItemSelected->image->setPixmap(pixOriginal);

    emit cancelButtonClicked();
    this->hide();

    brightnessSlider->setValue(0);
    contrastSlider->setValue(30);
    colorRadioButton->setChecked(false);
    grayscaleRadioButton->setChecked(true);

}

/// Save button pressed callback
void ConfWidget::onSaveButtonClicked()
{
    QString filename = view->cellItemSelected->getImagePath() +
            "/"+
            view->cellItemSelected->getImageName()+
            "."+
            view->cellItemSelected->getImageType();
    view->cellItemSelected->image->pixmap().save(filename);

    emit saveButtonClicked();
    this->hide();

    brightnessSlider->setValue(0);
    colorRadioButton->setChecked(false);
    grayscaleRadioButton->setChecked(true);

}

/// Resize event callback
void ConfWidget::resizeEvent(QResizeEvent*)
{
    histLabel->setGeometry(5,20,this->frameSize().width(),20);

    colorRadioButton->setGeometry(10,45,100,30);
    grayscaleRadioButton->setGeometry(120,45,100,30);

    histView->setGeometry(5,70,this->frameSize().width() - 10,100);
    histView->setSceneRect(0,0,histView->geometry().width()-20,histView->geometry().height()-20);

    brightnessLabel->setGeometry(5, 185, 80, 20);
    brightnessSlider->setGeometry(90, 185, this->frameSize().width() - 95-65, 20);
    brightnessSpinBox->setGeometry(this->frameSize().width()-65,185,60,20);

    contrastLabel->setGeometry(5, 215, 80, 20);
    contrastSlider->setGeometry(90, 215, this->frameSize().width() - 95-65, 20);
    contrastSpinBox->setGeometry(this->frameSize().width()-65,215,60,20);

    filterFrame->setGeometry(5, 245, this->frameSize().width(), 250);

    saveCancelFrame->setGeometry(0,this->frameSize().height()-50,this->frameSize().width(),50);

    bool histViewEmpty =  (histView->scene()->items().isEmpty());
    if(!histViewEmpty){
        histogram->setWidth(histView->sceneRect().width());
        histogram->setHeight(histView->sceneRect().height());
        drawHistogram(histogram->getType());
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
