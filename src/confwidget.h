#ifndef CONFWIDGET_H
#define CONFWIDGET_H

#include "sortwidget.h"
#include "histogram.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSpinBox>

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

class ConfWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ConfWidget(QWidget *parent = 0);
    virtual ~ConfWidget();

    QPixmap pixOriginal;
    QPixmap pixProcessed;

    cv::Mat matOriginal;
    cv::Mat matProcessed;

    GraphicsView *view;

protected:
    void resizeEvent(QResizeEvent *);
    void paintEvent(QPaintEvent *);

private:
    QFrame *saveCancelFrame;
    QHBoxLayout *saveCancelLayout;
    QPushButton *cancelButton;
    QPushButton *saveButton;
    QSpacerItem *leftSpacer;
    QSpacerItem *rightSpacer;

    QLabel *brightnessLabel;
    QSlider *brightnessSlider;
    QSpinBox *brightnessSpinBox;

    QLabel *contrastLabel;
    QSlider *contrastSlider;
    QDoubleSpinBox *contrastSpinBox;

    QButtonGroup *histogramButtonGroup;
    QRadioButton *colorRadioButton;
    QRadioButton *grayscaleRadioButton;

    QLabel *histLabel;
    QGraphicsView *histView;
    Histogram *histogram;

    QFrame *filterFrame;
    QVBoxLayout *filterVLayout;
    QHBoxLayout *filterHLayout;
    QPushButton *filterButtonMean;
    QPushButton *filterButtonSharpness;
    QPushButton *filterButtonLaplacian;
    QPushButton *filterButtonEdge;
    QPushButton *customFilterButton;
    QPushButton *originalFilterButton;
    QSpacerItem *filterLeftSpacer;
    QSpacerItem *filterRightSpacer;
    QButtonGroup *filterGroupButton;

signals:
    void cancelButtonClicked();
    void saveButtonClicked();
    void incrementProgressBar(int value, int maxValue);

public slots:
    void onCancelButtonClicked();
    void onSaveButtonClicked();
    void brightnessContrast();
    void drawHistogram(int type=0);
    void filter(QAbstractButton* button);
};

#endif // CONFWIDGET_H
