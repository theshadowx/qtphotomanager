#include "users.h"

/// Constructor of Users
Users::Users()
{
    userId = 0;
    username = "";
    password = "";

    nextUser = 0;
    previousUser = 0;
}

/// Constructor of Users
Users::Users(const QString username, const QString password, USER_PERMISSION permission, int id)
{
    userId = id;
    this->username = username;
    this->password = password;
    this->permission = permission;

    nextUser = 0;
    previousUser = 0;
}

Users::~Users()
{
}

/// Set username of the user
void Users::setUsername(const QString username)
{
    this->username = username;
}

/// Set password of the user
void Users::setPassword(const QString password)
{
    this->password = password;
}

/// Set permission of the user
void Users::setPermission(const Users::USER_PERMISSION permission)
{
    this->permission = permission;
}

/// Set id of the user
void Users::setUserId(int id)
{
    userId = id;
}

/// Get username of the user
QString Users::getUsername() const
{
    return username;
}

/// Get password of the user
QString Users::getPassword() const
{
    return password;
}

/// Get permission of the user
Users::USER_PERMISSION Users::getPermission() const
{
    return permission;
}

/// Get id of the user
int Users::getUserId() const
{
    return userId;
}

/// Convert the permission enum to QString
QString Users::enumPermissionToQString()
{
    QString permissionQStr = "";
    switch (permission) {
        case LEVEL_1 :
            permissionQStr = "LEVEL_1";
            break;
        case LEVEL_2:
            permissionQStr = "LEVEL_2";
            break;
        case LEVEL_3:
            permissionQStr = "LEVEL_3";
            break;
    default:
        permissionQStr = "";
    }

    return permissionQStr;
}
