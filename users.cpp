#include "users.h"

Users::Users()
{
    this->id = 0;
    username = "";
    password = "";

    nextUser = 0;
    previousUser = 0;
}

Users::Users(const QString username, const QString password, USER_PERMISSION permission, int id)
{
    this->id = id;
    this->username = username;
    this->password = password;
    this->permission = permission;

    nextUser = 0;
    previousUser = 0;
}

void Users::setUsername(const QString username)
{
    this->username = username;
}

void Users::setPassword(const QString password)
{
    this->password = password;
}

void Users::setPermission(const Users::USER_PERMISSION permission)
{
    this->permission = permission;
}

void Users::setId(int id)
{
    this->id = id;
}

QString Users::getUsername() const
{
    return username;
}

QString Users::getPassword() const
{
    return password;
}

Users::USER_PERMISSION Users::getPermission() const
{
    return permission;
}

int Users::getId() const
{
    return id;
}
