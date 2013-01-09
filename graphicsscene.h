#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QtGui>
#include <QtCore>
#include <QGraphicsScene>
#include "imagecellchain.h"


class GraphicsScene : public QGraphicsScene
{

public:
    explicit GraphicsScene(QObject *parent = 0);
    virtual ~GraphicsScene();


    ImageCellChain *imageCellChain;
    CellItem *cellItemSelected;

};
 
#endif // GRAPHICSSCENE_H
