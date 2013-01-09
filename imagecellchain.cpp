#include "imagecellchain.h"

/// Constructor of ImageCellChain
ImageCellChain::ImageCellChain(QObject *parent)
    :QObject(parent)
{
    cellItemCount = 0;
    cellItemRoot = 0;
    cellItemLast = 0;
}

/// Destructor of ImageCellChain
ImageCellChain::~ImageCellChain()
{
}

/// Add a CellItem to the chained list
void ImageCellChain::addCellItem(CellItem *cellItem)
{
    if(cellItemCount == 0){
        cellItemRoot = cellItem;
        cellItemLast = cellItem;
        cellItem->setImageId(0);
        cellItemCount = 1;
    }else{
        cellItemLast->nextCellItem = cellItem;
        cellItem->previousCellItem=cellItemLast;
        cellItem->nextCellItem = 0;
        cellItemLast = cellItem;
        cellItem->setImageId(cellItemCount);
        cellItemCount++;
    }
}

/// Add a CellItem to the chained list at the position id;
bool ImageCellChain::addCellItemAt(CellItem *cellItem, int id)
{
    bool ok = false;
    if(cellItemCount > id){
        CellItem *cellItemTmp = cellItemAt(id);
        if(cellItemTmp->previousCellItem){
            cellItem->previousCellItem = cellItemTmp->previousCellItem;
            cellItem->previousCellItem->nextCellItem = cellItem;
            cellItemTmp->previousCellItem = cellItem;
        }
        cellItem->nextCellItem = cellItemTmp;
        cellItemTmp->previousCellItem = cellItem;
        cellItem->setImageId(id);
        cellItemTmp->setImageId(id+1);
        while(cellItemTmp->nextCellItem){
            cellItemTmp = cellItemTmp->nextCellItem;
            cellItemTmp->setImageId(cellItemTmp->getImageId()+1);
        }
        ok = true;
    }else{
        ok = false;
    }
    return ok;
}

/// Delete a CellItem from the Chained list
void ImageCellChain::deleteCellItem(CellItem *cellItem)
{
    CellItem *cellItemTmp;

    if(cellItem == cellItemRoot){
        if(cellItemCount == 1){
            cellItemRoot = 0;
            cellItemLast = 0;
            cellItemTmp = 0;
        }else{
            cellItemRoot = cellItem->nextCellItem;
            cellItemRoot->previousCellItem = 0;
            cellItemTmp = cellItemRoot;
        }
    }else if(cellItem == cellItemLast){
        cellItemLast = cellItem->previousCellItem;
        cellItemLast->nextCellItem = 0;
        cellItemTmp = cellItemLast->nextCellItem;
    }else{
        cellItem->previousCellItem->nextCellItem = cellItem->nextCellItem;
        cellItem->nextCellItem->previousCellItem = cellItem->previousCellItem;
        cellItemTmp = cellItem->nextCellItem;
    }

    while(cellItemTmp){
        cellItemTmp->setImageId(cellItemTmp->getImageId()-1);
        cellItemTmp = cellItemTmp->nextCellItem;
    }

    cellItemCount--;
    delete cellItem->image;
    delete cellItem;
}

/// Delete a CellItem that has index id from the chained list
void ImageCellChain::deleteCellItemAt(int id)
{
    CellItem *cellItemTmp = cellItemAt(id);
    this->deleteCellItem(cellItemTmp);
}

/// Check whether the chained list contain a CellItem
bool ImageCellChain::contains(CellItem *cellItem) const
{
    CellItem *cellItemTmp = cellItemRoot;
    bool present = false;
    for(int i=0; i<cellItemCount;i++){
        if(cellItemTmp == cellItem){
            present = true;
            break;
        }else{
            cellItemTmp = cellItemTmp->nextCellItem;
        }
    }
    return present;
}

/// Check whether the chained list contain a CellItem which its name is imageName
bool ImageCellChain::contains(QString imageName) const
{
    CellItem *cellItemTmp = cellItemRoot;
    bool present = false;
    for(int i=0; i<cellItemCount;i++){
        if(cellItemTmp->getImageName() == imageName){
            present = true;
            break;
        }else{
            cellItemTmp = cellItemTmp->nextCellItem;
        }
    }
    return present;

}

/// Get a CellItem from the chained list that has index id
CellItem *ImageCellChain::cellItemAt(int id) const
{
    CellItem *cellItemTmp = cellItemRoot;
    while(cellItemTmp->getImageId() != id){
        cellItemTmp = cellItemTmp->nextCellItem;
        if(!cellItemTmp)
            return 0;
    }
    return cellItemTmp;
}

/// Get the number of element in the chained list
int ImageCellChain::getCount() const
{
    return cellItemCount;
}

void ImageCellChain::update(DataBase *database)
{
    for(int i=cellItemCount-1; i>=0;i--)
        this->deleteCellItemAt(i);

    int imageNumLines = database->getImageNumlines();
    CellItem *cellItem = 0;

    for(int i=0; i<imageNumLines; i++){
        cellItem = database->getImageDb(i);
        this->addCellItem(cellItem);
    }

    emit updated();
}
