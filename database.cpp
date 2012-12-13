#include "database.h"

DataBase::DataBase():QSqlDatabase()
{
    numLines = 0;
    homePath = QDir(QDir::homePath() + "/.photoManager");
    if(!homePath.exists())
        QDir().mkdir(homePath.path());

    QDir().setCurrent(homePath.absolutePath());
    userDbFile.setFileName("usersDb.txt");

    if(!userDbFile.isOpen()){
      userDbFile.open(QFile::Append | QFile::ReadWrite);
    }
    userDbFile.seek(0);
    while(!userDbFile.atEnd()){
        userDbFile.readLine();
        numLines ++;
    }
}

DataBase::~DataBase(){}

void DataBase::addUserDb(Users* user)
{
    QTextStream outStream(&userDbFile);
    outStream << QString("%1").arg(user->getId()) + " " + user->getUsername() + " " + user->getPassword() + " " + QString("%1").arg(user->getPermission()) << endl;
    numLines++;
}

Users* DataBase::getUserDb(int id)
{
    Q_ASSERT(id < numLines);

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

int DataBase::getNumlines() const
{
    return numLines;
}

bool DataBase::deleteUserDb(QString username)
{
    QTextStream inStream(&userDbFile);
    QStringList line;
    QFile tmpFile("tmp.txt");
    tmpFile.open(QFile::Append);
    QTextStream tmpInStream(&tmpFile);
    int userLine = 0;
    bool userExist = false;
    inStream.seek(0);
    line = inStream.readLine().split(" ");
    for(int i=0; i<numLines; i++){
        if(line.at(1) != username){
            line = inStream.readLine().split(" ");
        }else{
            userLine = i;
            numLines --;
            userExist = true;
        }
    }

    inStream.seek(0);
    for(int i=0; i<numLines+1; i++){
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

    return userExist;
}


