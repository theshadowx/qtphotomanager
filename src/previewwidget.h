#ifndef PREVIEWWIDGET_H
#define PREVIEWWIDGET_H

#include "imagecellchain.h"

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QDialogButtonBox>

#include <QScrollBar>

class PreviewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PreviewWidget(QWidget *parent = 0);
    virtual ~PreviewWidget();

    void adjustCellItems();
    void showImage(CellItem* cellItem);

    ImageCellChain* imageCellChain;
    CellItem *cellItemSelected;

protected:
    void resizeEvent(QResizeEvent* );
    bool eventFilter(QObject *obj, QEvent *event);


private:
    QDialogButtonBox *buttonBox;
    QGraphicsView *mainView;
    QGraphicsView *listView;
    QFrame *frame;
    
signals:
    void cancelButtonClicked();
    
public slots:
    void onButtonClicked(QAbstractButton* button = 0);

    
};

#endif // PREVIEWWIDGET_H
