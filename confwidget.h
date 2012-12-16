#ifndef CONFWIDGET_H
#define CONFWIDGET_H

#include <QWidget>
#include <QtGui>
#include <QtCore>
#include "sortwidget.h"

#ifdef Q_OS_LINUX
#include "thirdparty/opencv/include/opencv2/core/core.hpp"
#include "thirdparty/opencv/include/opencv2/imgproc/imgproc.hpp"
#include "thirdparty/opencv/include/opencv2/highgui/highgui.hpp"
#else
#endif


class graphicsView;

class ConfWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ConfWidget(QWidget *parent = 0);
    void resizeEvent(QResizeEvent *);

    QPixmap pixOriginal;
    QPixmap pixProcessed;
    QImage imgOriginal;
    QImage imgProcessed;

    graphicsView *view;
    QGraphicsView *histView;

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
    QGraphicsPixmapItem *histPixmap;

signals:
    void cancelButton_clicked();
    void saveButton_clicked();

public slots:
    void on_cancelButton_clicked();
    void on_saveButton_clicked();
    void brightnessContrast();
    void showHistogram();

protected:


    
};

#endif // CONFWIDGET_H
