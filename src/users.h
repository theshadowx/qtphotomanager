#ifndef USERS_H
#define USERS_H

#include <QString>


class Users
{
public:
    enum USER_PERMISSION{LEVEL_1 = 0,LEVEL_2 = 1,LEVEL_3 = 2};

    Users();
    explicit Users(QString const username,
                   QString const password,
                   Users::USER_PERMISSION permission,
                   QString email = "",
                   int id=0);
    virtual ~Users();

    void setUsername(QString const username);
    void setPassword(QString const password);
    void setPermission(const USER_PERMISSION permission);
    void setEmail(QString email);
    void setUserId(int id);

    QString getUsername() const;
    QString getPassword() const;
    USER_PERMISSION getPermission() const;
    QString getEmail() const;
    int getUserId() const;

    QString enumPermissionToQString();
    Users::USER_PERMISSION qstringToEnumPermission(QString permissionQStr);

    Users *nextUser;
    Users *previousUser;

private:
    int userId;
    QString username;
    QString password;
    QString email;
    USER_PERMISSION permission;

};

#endif // USERS_H
