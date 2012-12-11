#include "imagecellchain.h"

ImageCellChain::ImageCellChain()
{
    cellItemCount = 0;
    cellItemRoot = 0;
    cellItemLast = 0;
}

void ImageCellChain::addCellItem(CellItem *cellItem)
{
    if(cellItemCount == 0){
        cellItemRoot = cellItem;
        cellItemLast = cellItem;
        cellItemCount = 1;
    }else{
        cellItemLast->nextCellItem = cellItem;
        cellItem->previousCellItem=cellItemLast;
        cellItem->nextCellItem = 0;
        cellItemLast = cellItem;
        cellItem->setId(cellItemCount);
        cellItemCount++;
    }
}

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
        cellItem->setId(id);
        cellItemTmp->setId(id+1);
        while(cellItemTmp->nextCellItem){
            cellItemTmp = cellItemTmp->nextCellItem;
            cellItemTmp->setId(cellItemTmp->getId()+1);
        }
        ok = true;
    }else{
        ok = false;
    }
    return ok;
}

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
        cellItemTmp->setId(cellItemTmp->getId()-1);
        cellItemTmp = cellItemTmp->nextCellItem;
    }

    cellItemCount--;
    delete cellItem;
}

void ImageCellChain::deleteCellItemAt(int id)
{
    CellItem *cellItemTmp = cellItemAt(id);
    this->deleteCellItem(cellItemTmp);
}

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

CellItem *ImageCellChain::cellItemAt(int id) const
{
    CellItem *cellItemTmp = cellItemRoot;
    while(cellItemTmp->getId() != id){
        cellItemTmp = cellItemTmp->nextCellItem;
        if(!cellItemTmp)
            return 0;
    }
    return cellItemTmp;
}

int ImageCellChain::getCount() const
{
    return cellItemCount;
}
