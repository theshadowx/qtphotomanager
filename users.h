#ifndef USERS_H
#define USERS_H

#include <QObject>
#include <QtGui>
#include <QtCore>

class Users
{
public:
    enum USER_PERMISSION{LEVEL_1 = 1,LEVEL_2 = 2,LEVEL_3 = 3};

    Users();
    Users(QString const username, QString const password, Users::USER_PERMISSION permission, int id=0);
    void setUsername(QString const username);
    void setPassword(QString const password);
    void setPermission(const Users::USER_PERMISSION permission);
    void setId(int id);

    QString getUsername() const;
    QString getPassword() const;
    USER_PERMISSION getPermission() const;
    int getId() const;

    Users *nextUser;
    Users *previousUser;

private:
    int id;
    QString username;
    QString password;
    USER_PERMISSION permission;



};

#endif // USERS_H
