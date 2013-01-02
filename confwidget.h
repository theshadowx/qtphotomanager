#ifndef CONFWIDGET_H
#define CONFWIDGET_H

#include <QWidget>
#include <QtGui>
#include <QtCore>
#include "sortwidget.h"

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

class ConfWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ConfWidget(QWidget *parent = 0);

    QPixmap pixOriginal;
    QPixmap pixProcessed;

    cv::Mat matOriginal;
    cv::Mat matProcessed;

    GraphicsView *view;
    QGraphicsView *histView;

protected:
    void resizeEvent(QResizeEvent *);
    void paintEvent(QPaintEvent *);

private:
    QHBoxLayout *layout;
    QPushButton *cancelButton;
    QPushButton *saveButton;
    QSpacerItem *leftSpacer;
    QSpacerItem *rightSpacer;
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

};

#endif // CONFWIDGET_H
