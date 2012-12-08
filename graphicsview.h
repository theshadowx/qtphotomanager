#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QtSql>
#include "graphicsscene.h"
#include "database.h"

class ConfWidget;

class graphicsView : public QGraphicsView
{
    Q_OBJECT
public:

    graphicsView(QWidget *parent=0);
    graphicsView(const QString &table, const QString &images, QWidget *parent=0);

    void adjustCellItems();

    graphicsScene *scene;
    graphicsScene *sceneProcessing;

public slots:

protected:
    virtual void mousePressEvent(QMouseEvent* event);

};
 
#endif // GRAPHICSVIEW_H
