#ifndef IMAGECELLCHAIN_H
#define IMAGECELLCHAIN_H

#include "cellitem.h"

class ImageCellChain
{
public:
    ImageCellChain();

    void addCellItem(CellItem *cellItem);
    bool addCellItemAt(CellItem *cellItem,int id);
    void deleteCellItem(CellItem *cellItem);
    void deleteCellItemAt(int id);
    bool contains(CellItem *cellItem) const;
    CellItem* cellItemAt(int id) const;
    int getCount() const;

private:
    int cellItemCount;
    CellItem *cellItemRoot;
    CellItem *cellItemLast;
};

#endif // IMAGECELLCHAIN_H
