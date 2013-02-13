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
    for(int i=0;i<cellItemCount;i++){
        deleteCellItem(cellItemAt(i));
    }
    cellItemCount = 0;
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
        }else{
            cellItemRoot = cellItem;
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
        cellItemCount++;
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

void ImageCellChain::swap(CellItem *cell1, CellItem *cell2)
{

    CellItem *cellTmp = 0;
    CellItem *cellItem1 = 0;
    CellItem *cellItem2 = 0;
    int cellId1 = 0;
    int cellId2 = 0;

    if(cell1->getImageId() < cell2->getImageId()){
        cellItem1 = cell1;
        cellItem2 = cell2;
        cellId1 = cell1->getImageId();
        cellId2 = cell2->getImageId();
    }else{
        cellItem1 = cell2;
        cellItem2 = cell1;
        cellId1 = cell2->getImageId();
        cellId2 = cell1->getImageId();
    }

    /// next
    if(cellItem2 != cellItemLast){
        cellTmp = cellItem2->nextCellItem;
        cellItem2->nextCellItem = cellItem1->nextCellItem;
        cellItem1->nextCellItem->previousCellItem = cellItem2;
        cellItem1->nextCellItem = cellTmp;
        cellTmp->previousCellItem = cellItem1;
    }else if(cellItemCount>2){
        cellItem2->nextCellItem = cellItem1->nextCellItem;
        cellItem1->nextCellItem->previousCellItem = cellItem2;
        cellItem1->nextCellItem = 0;
    }else{
         cellItem2->nextCellItem = cellItem1;
         cellItem1->nextCellItem = 0;
    }

    /// prev
    if(cellItem1 != cellItemRoot){
        cellTmp = cellItem1->previousCellItem;
        cellItem1->previousCellItem = cellItem2->previousCellItem;
        cellItem2->previousCellItem->nextCellItem = cellItem1;
        cellItem2->previousCellItem = cellTmp;
        cellTmp->nextCellItem = cellItem2;
    }else if(cellItemCount>2){
        cellItem1->previousCellItem = cellItem2->previousCellItem;
        cellItem2->previousCellItem->nextCellItem = cellItem1;
        cellItem2->previousCellItem = 0;
    }else{
        cellItem1->previousCellItem = cellItem2;
        cellItem2->previousCellItem = 0;
    }

    if(cellItem1 == cellItemRoot)
        cellItemRoot = cellItem2;

    if(cellItem2 == cellItemLast)
        cellItemLast = cellItem1;

    cellItem1->setImageId(cellId2);
    cellItem2->setImageId(cellId1);
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
