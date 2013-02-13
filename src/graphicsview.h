#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include "graphicsscene.h"
#include "database.h"

#include <QGraphicsView>
#include <QScrollBar>
#include <QMouseEvent>


//class ConfWidget;

class GraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit GraphicsView(QWidget *parent=0);
    virtual ~GraphicsView();

    GraphicsScene *scene;
    GraphicsScene *sceneProcessing;
    Users *currentUser;
    ImageCellChain *imageCellChain;
    CellItem *cellItemSelected;

private:
    bool ctrlClicked;
    bool ctrlToggled;
    QList<CellItem*> selectedCellItemsList;

protected:
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    virtual void resizeEvent(QResizeEvent *);

public slots:
    void setupProcessingMode(CellItem *cellItem);
    void setupGlobalMode();
    void adjustCellItems();
    void updateScene();

signals:
    void cellItemClicked(CellItem *item);
    void cellItemDeleted(QList<CellItem*> cellItems);

};
 
#endif // GRAPHICSVIEW_H
