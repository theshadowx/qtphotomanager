#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>


class DataBase : public QSqlDatabase
{
public:
    DataBase();
    virtual ~DataBase();

};

#endif //USERDATABASE_H
