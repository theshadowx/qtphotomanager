#ifndef CONFWIDGET_H
#define CONFWIDGET_H

#include <QWidget>
#include <QtGui>
#include <QtCore>

#ifdef Q_OS_LINUX
#include "thirdparty/opencv/include/opencv2/core/core.hpp"
#include "thirdparty/opencv/include/opencv2/highgui/highgui.hpp"
#include "thirdparty/opencv/include/opencv2/imgproc/imgproc.hpp"
#else
#endif


class graphicsView;

class ConfWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ConfWidget(QWidget *parent = 0);
    void resizeEvent(QResizeEvent *);

    graphicsView *view;

    QPixmap pixOriginal;
    QImage imgOriginal;
    QImage imgProcessed;

#ifdef Q_OS_LINUX
    cv::Mat matOriginal;
    cv::Mat matProcessed;
#endif

private:
    QPushButton *cancelButton;
    QPushButton *saveButton;
    QSlider *brightnessSlider;
    QLabel *brightnessLabel;
    QSlider *contrastSlider;
    QLabel *contrastLabel;

signals:
    
public slots:
    void on_cancelButton_clicked();
    void brightnessValue();
    void contrastValue();

protected:


    
};

#endif // CONFWIDGET_H
