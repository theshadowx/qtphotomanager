#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include "graphicsscene.h"
#include "database.h"

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

protected:
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent* event);

public slots:
    void adjustCellItems();
    void updateScene();

signals:
    void cellItemClicked(CellItem *item);

};
 
#endif // GRAPHICSVIEW_H
