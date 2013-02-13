#ifndef DATABASEWIDGET_H
#define DATABASEWIDGET_H

#include "database.h"
#include "comboboxdelegate.h"
#include "piechart.h"

#include <QWidget>
#include <QTableView>
#include <QStandardItemModel>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include <QGraphicsView>
#include <QTextEdit>

class DatabaseWidget : public QWidget
{
    Q_OBJECT
public:

    explicit DatabaseWidget(DataBase *database, QWidget *parent = 0);
    virtual ~DatabaseWidget();

    void buildAChart();

protected:
    void resizeEvent(QResizeEvent* );
    void paintEvent(QPaintEvent *);

private:
    DataBase *database;

    QTableView *userTableView;
    QTableView *imageTableView;

    QStandardItemModel *userModel;
    QStandardItemModel *imageModel;

    ComboBoxDelegate *userDelegate;
    ComboBoxDelegate *imageSizeDelegate;
    ComboBoxDelegate *imageCfdyDelegate;

    QFrame *imageDbFrame;

    QComboBox *pieParamSelector;
    QGraphicsView *pieChartView;
    QLabel *legendLine1;
    QLabel *legendLine2;
    QLabel *legendLine3;
    PieChart *pieChartItem;

    QGraphicsView *imageView;
    ImageItem *imageItem;

    QLabel *titleLabel;

    QFrame *saveCancelFrame;
    QHBoxLayout *saveCancellayout;
    QPushButton *cancelButton;
    QPushButton *saveButton;
    QSpacerItem *leftSpacer;
    QSpacerItem *rightSpacer;

    bool imageDbModified;
    bool userDbModified;

    int jpg;
    int bmp;
    int png;
    int small;
    int medium;
    int large;
    int Rs;
    int Fs;
    int low;
    int average;
    int high;
    int total;

signals:
    void cancelButtonClicked();
    void saveButtonClicked();
    void imageDbChanged(DataBase *);
    void userDbChanged(DataBase *);
    void chartUpdated(QString);

public slots:
    void updateImageTable();
    void updateUserTable();
    void onCancelButtonClicked();
    void onSaveButtonClicked();
    void onUserDbChanged();
    void onImageDbChanged();
    bool onImageDeleted(QList<CellItem *> cellItemList);
    void showUserDb();
    void showImageDb();
    void drawChart(QString);
    void updateChart();
    void updateImageView(QModelIndex index);
    
};

#endif // DATABASEWIDGET_H
