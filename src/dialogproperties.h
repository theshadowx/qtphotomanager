#ifndef DIALOGPROPERTIES_H
#define DIALOGPROPERTIES_H

#include "cellitem.h"

#include <QDialog>
#include <QLabel>
#include <QTableWidget>
#include <QDialogButtonBox>
#include <QGraphicsView>
#include <QPushButton>
#include <QDir>
#include <QFile>
#include <QImageReader>


class DialogProperties: public QDialog
{
    Q_OBJECT
public:
    DialogProperties(CellItem *cellItem,QWidget *parent = 0);
    ~DialogProperties();

    void updateData();

    CellItem *currentCellItem;

private:
    QDialogButtonBox *buttonBox;
    QPushButton *nextImageButton;
    QPushButton *previousImageButton;
    QPushButton *closeButton;

    QTabWidget *tabWidget;
    QWidget *pageGeneral;

    QLabel *nameLabel;
    QLabel *widthLabel;
    QLabel *heightLabel;
    QLabel *typeLabel;
    QLabel *sizeLabel;
    QLabel *weightLabel;
    QLabel *priceLabel;
    QLabel *cfdyLabel;
    QLabel *pathLabel;


    QLabel *nameData;
    QLabel *widthData;
    QLabel *heightData;
    QLabel *typeData;
    QLabel *sizeData;
    QLabel *weightData;
    QLabel *priceData;
    QLabel *cfdyData;
    QLabel *pathData;

    QGraphicsView *imageView;
    ImageItem *image;

public slots:
    void onPreviousImageClicked();
    void onNextImageClicked();

};

#endif // DIALOGPROPERTIES_H
