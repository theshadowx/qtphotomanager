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

    void addUserDb(Users *user);
    Users* getUserDb(int id);
    int getUserNumlines() const;
    bool deleteUserDb(QString username);

    void addImageDb(CellItem *cellItem);
    CellItem* getImageDb(int id);
    int getImageNumlines() const;
    bool deleteImageDb(QString imageName);

private:

    QDir homePath;
    QDir userPath;

    QFile userDbFile;
    int userNumLines;

    QFile imageDbFile;
    int imageNumLines;

};

#endif //USERDATABASE_H
