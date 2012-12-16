#include "database.h"

DataBase::DataBase():QSqlDatabase()
{
    userNumLines = 0;
    imageNumLines = 0;

    homePath = QDir(QDir::homePath() + "/.photoManager");
    if(!homePath.exists())
        QDir().mkdir(homePath.path());
    QDir().setCurrent(homePath.absolutePath());
    userDbFile.setFileName("usersDb.txt");
    imageDbFile.setFileName("imagesDb.txt");

    if(!userDbFile.isOpen()){
      userDbFile.open(QFile::Append | QFile::ReadWrite);
    }
    userDbFile.seek(0);
    while(!userDbFile.atEnd()){
        userDbFile.readLine();
        userNumLines ++;
    }

    if(!imageDbFile.isOpen()){
      imageDbFile.open(QFile::Append | QFile::ReadWrite);
    }
    imageDbFile.seek(0);
    while(!imageDbFile.atEnd()){
        imageDbFile.readLine();
        imageNumLines ++;
    }
}

DataBase::~DataBase(){}


/// User DataBase Functions ///

void DataBase::addUserDb(Users* user)
{
    QTextStream outStream(&userDbFile);
    outStream << QString("%1").arg(user->getId()) + " " + user->getUsername() + " " + user->getPassword() + " " + QString("%1").arg(user->getPermission()) << endl;
    userNumLines++;
}

Users* DataBase::getUserDb(int id)
{
    Q_ASSERT(id < userNumLines);

    QTextStream inStream(&userDbFile);
    QStringList line;
    inStream.seek(0);
    line = inStream.readLine().split(" ");
    while(line.at(0).toInt() != id){
        line = inStream.readLine().split(" ");
    }

    Users *user = new Users();
    user->setId(line.at(0).toInt());
    user->setUsername(line.at(1));
    user->setPassword(line.at(2));
    user->setPermission((Users::USER_PERMISSION)QString(line.at(3)).toInt());

    return user;
}

int DataBase::getUserNumlines() const
{
    return userNumLines;
}

bool DataBase::deleteUserDb(QString username)
{
    QTextStream inStream(&userDbFile);
    QStringList line;
    int userLine = 0;
    bool userExist = false;
    inStream.seek(0);
    line = inStream.readLine().split(" ");
    for(int i=0; i<userNumLines; i++){
        if(line.at(1) != username){
            line = inStream.readLine().split(" ");
        }else{
            userLine = i;
            userNumLines --;
            userExist = true;
            break;
        }
    }
    if(userExist){
        QFile tmpFile("tmp.txt");
        tmpFile.open(QFile::Append);
        QTextStream tmpInStream(&tmpFile);
        inStream.seek(0);
        for(int i=0; i<userNumLines+1; i++){
            if(i < userLine){
                line = inStream.readLine().split(" ");
                tmpInStream << line.at(0)  << " "  << line.at(1)  << " "  << line.at(2)  << " "  << line.at(3) << endl;
            }else if(i > userLine){
                line = inStream.readLine().split(" ");
                tmpInStream << QString().setNum(line.at(0).toInt()-1)  << " "  << line.at(1)  << " "  << line.at(2)  << " "  << line.at(3) << endl;
            }else{
                inStream.readLine();
            }
        }
        tmpFile.close();
        userDbFile.close();
        userDbFile.remove();
        userDbFile.setFileName("tmp.txt");
        userDbFile.rename("usersDb.txt");
        userDbFile.open(QFile::Append | QFile::ReadWrite);
    }

    return userExist;
}

/// Image DataBase Functions ///

void DataBase::addImageDb(CellItem* cellItem)
{
    QTextStream outStream(&imageDbFile);
    outStream << QString("%1").arg(cellItem->getId()) + " " +
                 cellItem->getImageName() + " " +
                 cellItem->getImagePath() + " " +
                 cellItem->getImageType() + " " +
                 QString("%1").arg(cellItem->getImagePrice()) + " " +
                 QString("%1").arg(cellItem->getImageCfdy()) << endl;
    imageNumLines++;
}

CellItem* DataBase::getImageDb(int id)
{
    Q_ASSERT(id < imageNumLines);

    QTextStream inStream(&imageDbFile);
    QStringList line;
    inStream.seek(0);
    line = inStream.readLine().split(" ");
    while(line.at(0).toInt() != id){
        line = inStream.readLine().split(" ");
    }

    CellItem *cellItem = new CellItem();
    cellItem->setId(line.at(0).toInt());
    cellItem->setImageName(line.at(1));
    cellItem->setImagePath(line.at(2));
    cellItem->setImageType(line.at(3));
    cellItem->setImagePrice(line.at(4).toInt());
    cellItem->setImageCfdy((CellItem::IMAGE_CONFIDENTILITY)QString(line.at(5)).toInt());
    cellItem->image->setPixmap(QPixmap(cellItem->getImagePath() + QDir().separator() + cellItem->getImageName() + "." + cellItem->getImageType()));
    cellItem->image->adjust();
    return cellItem;
}

int DataBase::getImageNumlines() const
{
    return imageNumLines;
}

bool DataBase::deleteImageDb(QString imageName)
{
    QTextStream inStream(&imageDbFile);
    QStringList line;
    int imageLine = 0;
    bool imageExist = false;
    inStream.seek(0);
    line = inStream.readLine().split(" ");
    for(int i=0; i<imageNumLines; i++){
        if(line.at(1) != imageName){
            line = inStream.readLine().split(" ");
        }else{
            imageLine = i;
            imageNumLines --;
            imageExist = true;
            break;
        }
    }

    if(imageExist){
        QFile tmpFile("tmp.txt");
        tmpFile.open(QFile::Append);
        QTextStream tmpInStream(&tmpFile);
        inStream.seek(0);
        for(int i=0; i<imageNumLines+1; i++){
            if(i < imageLine){
                line = inStream.readLine().split(" ");
                tmpInStream << line.at(0)  << " "  << line.at(1)  << " "  << line.at(2)  << " "  << line.at(3) << " "  << line.at(4) << " "  << line.at(5) << endl;
            }else if(i > imageLine){
                line = inStream.readLine().split(" ");
                tmpInStream << QString().setNum(line.at(0).toInt()-1)  << " "  << line.at(1)  << " "  << line.at(2)  << " "  << line.at(3) << " "  << line.at(4) << " "  << line.at(5) << endl;
            }else{
                inStream.readLine();
            }
        }
        tmpFile.close();
        imageDbFile.close();
        imageDbFile.remove();
        imageDbFile.setFileName("tmp.txt");
        imageDbFile.rename("imagesDb.txt");
        imageDbFile.open(QFile::Append | QFile::ReadWrite);
    }

    return imageExist;
}
