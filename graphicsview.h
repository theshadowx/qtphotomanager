#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include "graphicsscene.h"
#include "database.h"

//class ConfWidget;

class GraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    GraphicsView(QWidget *parent=0);

    void adjustCellItems();

    GraphicsScene *scene;
    GraphicsScene *sceneProcessing;

protected:
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent* event);

signals:
    void cellItemClicked(CellItem *item);

};
 
#endif // GRAPHICSVIEW_H
