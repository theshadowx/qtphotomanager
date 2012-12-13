#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include "users.h"


class DataBase : public QSqlDatabase
{
public:
    DataBase();
    virtual ~DataBase();

    void addUserDb(Users *user);
    Users* getUserDb(int id);
    int getNumlines() const;
    bool deleteUserDb(QString username);

private:
    QFile userDbFile;
    QDir homePath;
    int numLines;

};

#endif //USERDATABASE_H
