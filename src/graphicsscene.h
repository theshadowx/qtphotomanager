#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include "imagecellchain.h"

#include <QGraphicsScene>

class GraphicsScene : public QGraphicsScene
{

public:
    explicit GraphicsScene(QObject *parent = 0);
    virtual ~GraphicsScene();

};
 
#endif // GRAPHICSSCENE_H
