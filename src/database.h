#ifndef DATABASE_H
#define DATABASE_H

#include "users.h"
#include "cellitem.h"

#include <QFile>
#include <QDir>
#include <QTextStream>

class DataBase
{
public:
    DataBase();
    virtual ~DataBase();

    void addUserDb(Users *user);
    Users* getUserDb(int id);
    int getUserNumlines() const;
    bool deleteUserDb(const QString username);
    bool clearUserDb();
    void closeUserDb();

    void setImageDB(QString username,Users::USER_PERMISSION permission);
    void addImageDb(CellItem *cellItem);
    CellItem* getImageDb(int id);
    int getImageNumlines() const;
    bool deleteImageDb(const QString imageName);
    bool deleteImageDb(const QList<CellItem*> cellItemList);
    bool clearImageDb();
    void closeImageDb();

private:

    QDir homePath;
    QDir userPath;

    QFile userDbFile;
    int userNumLines;

    QFile imageDbFile;
    int imageNumLines;

};

#endif //DATABASE_H
