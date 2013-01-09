#include "database.h"

/// Constructor of Database
DataBase::DataBase():QSqlDatabase()
{
#ifdef Q_OS_LINUX
    homePath = QDir(QDir::homePath() + "/.photoManager");
#else
    homePath = QDir(QDir::homePath() + "/photoManager");
#endif

    userNumLines = 0;
    imageNumLines = 0;

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

/// Destructor of database
DataBase::~DataBase()
{
}

/// User DataBase Functions ///
void DataBase::addUserDb(Users* user)
{
    QTextStream outStream(&userDbFile);
    outStream << QString("%1").arg(user->getUserId()) + " " + user->getUsername() + " " + user->getPassword() + " " + QString("%1").arg(user->getPermission()) << endl;
    userNumLines++;
}

/// ******************************************************************** ///
///                     User DataBase Functions
/// ******************************************************************** ///

/// Get the user that has index id
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
    user->setUserId(line.at(0).toInt());
    user->setUsername(line.at(1));
    user->setPassword(line.at(2));
    user->setPermission((Users::USER_PERMISSION)QString(line.at(3)).toInt());

    return user;
}

/// Get number of users present in database
int DataBase::getUserNumlines() const
{
    return userNumLines;
}

/// Delete a user from database
bool DataBase::deleteUserDb(const QString username)
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

/// Clear all user database
bool DataBase::clearUserDb()
{
    userNumLines = 0;
    userDbFile.close();
    userDbFile.remove();
    userDbFile.setFileName("usersDb.txt");
    return userDbFile.open(QFile::Append | QFile::ReadWrite);

}

/// ******************************************************************** ///
///                     Image DataBase Functions
/// ******************************************************************** ///

/// add image to image database
void DataBase::addImageDb(CellItem* cellItem)
{
    QTextStream outStream(&imageDbFile);
    outStream << QString("%1").arg(cellItem->getImageId()) + " " +
                 cellItem->getImageName() + " " +
                 cellItem->getImagePath() + " " +
                 cellItem->getImageType() + " " +
                 QString("%1").arg(cellItem->getImagePrice()) + " " +
                 QString("%1").arg(cellItem->getImageCfdy()) + " " +
                 QString("%1").arg(cellItem->getImageSize()) << endl;
    imageNumLines++;
}

/// get image from database that has index id
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
    cellItem->setImageId(line.at(0).toInt());
    cellItem->setImageName(line.at(1));
    cellItem->setImagePath(line.at(2));
    cellItem->setImageType(line.at(3));
    cellItem->setImagePrice(line.at(4).toInt());
    cellItem->setImageCfdy((CellItem::IMAGE_CONFIDENTIALITY)QString(line.at(5)).toInt());
    cellItem->setImageSize((CellItem::IMAGE_SIZE)QString(line.at(6)).toInt());
    cellItem->image->setPixmap(QPixmap(cellItem->getImagePath() + QDir().separator() + cellItem->getImageName() + "." + cellItem->getImageType()));
    cellItem->image->adjust();
    return cellItem;
}

/// Get the number of images in database
int DataBase::getImageNumlines() const
{
    return imageNumLines;
}

/// Delete image from database
bool DataBase::deleteImageDb(const QString imageName)
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
                tmpInStream << line.at(0)  << " "  << line.at(1)  << " "  << line.at(2)  << " "  << line.at(3) << " "  << line.at(4) << " "  << line.at(5) << " "  << line.at(6) << endl;
            }else if(i > imageLine){
                line = inStream.readLine().split(" ");
                tmpInStream << QString().setNum(line.at(0).toInt()-1)  << " "  << line.at(1)  << " "  << line.at(2)  << " "  << line.at(3) << " "  << line.at(4) << " "  << line.at(5) << " "  << line.at(6) << endl;
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

/// Clear all image database
bool DataBase::clearImageDb()
{
    imageNumLines = 0;
    imageDbFile.close();
    imageDbFile.remove();
    imageDbFile.setFileName("imagesDb.txt");
    return imageDbFile.open(QFile::Append | QFile::ReadWrite);
}
