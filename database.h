#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include "users.h"
#include "cellitem.h"


class DataBase : public QSqlDatabase
{
public:
    DataBase();
    virtual ~DataBase();

    // User Database
    void addUserDb(Users *user);
    Users* getUserDb(int id);
    int getUserNumlines() const;
    bool deleteUserDb(QString username);


    //image Database
    void addImageDb(CellItem *cellItem);
    CellItem* getImageDb(int id);
    int getImageNumlines() const;
    bool deleteImageDb(QString imageName);

private:

    QDir homePath;
    QDir userPath;
    QFile userDbFile;
    QFile imageDbFile;
    int userNumLines;
    int imageNumLines;

};

#endif //USERDATABASE_H
