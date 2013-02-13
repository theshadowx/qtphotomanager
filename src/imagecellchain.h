#ifndef IMAGECELLCHAIN_H
#define IMAGECELLCHAIN_H

#include "cellitem.h"
#include "database.h"

class ImageCellChain: public QObject
{
    Q_OBJECT
public:
    explicit ImageCellChain(QObject *parent=0);
    virtual ~ImageCellChain();

    void addCellItem(CellItem *cellItem);
    bool addCellItemAt(CellItem *cellItem,int id);

    void deleteCellItem(CellItem *cellItem);
    void deleteCellItemAt(int id);

    bool contains(CellItem *cellItem) const;
    bool contains(QString imageName) const;
    CellItem* cellItemAt(int id) const;
    int getCount() const;

    void swap(CellItem *cell1, CellItem *cell2);

    CellItem *cellItemRoot;
    CellItem *cellItemLast;

private:
    int cellItemCount;

public slots:
    void update(DataBase *database);

signals:
    void updated();
};

#endif // IMAGECELLCHAIN_H
