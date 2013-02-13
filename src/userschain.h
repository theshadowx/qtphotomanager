#ifndef USERSCHAIN_H
#define USERSCHAIN_H

#include "users.h"
#include "database.h"

class UsersChain : public QObject
{
    Q_OBJECT
public:
    UsersChain(QObject *parent=0);
    virtual ~UsersChain();

    void addUser(Users *user);
    bool addUserAt(Users* user,int id);

    void deleteUser(Users *user);
    void deleteUserAt(int id);

    Users* userAt(int id) const;
    Users* getUser(QString username, QString password) const;
    bool containsUser(QString username) const;

private:
    int usersCount;
    Users *userRoot;
    Users *userLast;

public slots:
    void update(DataBase *database);
};

#endif // USERSCHAIN_H
