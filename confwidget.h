#ifndef CONFWIDGET_H
#define CONFWIDGET_H

#include <QWidget>
#include <QtGui>
#include <QtCore>
#include "sortwidget.h"

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"



class graphicsView;

class ConfWidget : public QWidget
{
    Q_OBJECT
public:
    /*!
     *
     */
    explicit ConfWidget(QWidget *parent = 0);
    /*!
     *
     */
    void resizeEvent(QResizeEvent *);

    QPixmap pixOriginal;
    QPixmap pixProcessed;
    QImage imgOriginal;
    QImage imgProcessed;

    graphicsView *view;
    QGraphicsView *histView;

    cv::Mat matOriginal;
    cv::Mat matProcessed;

private:
    QPushButton *cancelButton;
    QPushButton *saveButton;
    QSlider *brightnessSlider;
    QLabel *brightnessLabel;
    QSlider *contrastSlider;
    QLabel *contrastLabel;
    QGraphicsPixmapItem *histPixmap;

signals:
    /*!
     *
     */
    void cancelButton_clicked();
    /*!
     *
     */
    void saveButton_clicked();

public slots:
    /*!
     *
     */
    void on_cancelButton_clicked();
    /*!
     *
     */
    void on_saveButton_clicked();
    /*!
     *
     */
    void brightnessContrast();
    /*!
     *
     */
    void showHistogram();

    
};

#endif // CONFWIDGET_H
