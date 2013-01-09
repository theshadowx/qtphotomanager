#include "userschain.h"

/// Constructor of UserChain
UsersChain::UsersChain(QObject *parent)
    :QObject(parent)
{
    usersCount = 0;
    userRoot = 0;
    userLast = 0;
}

UsersChain::~UsersChain()
{
}

/// Add user to the chained list
void UsersChain::addUser(Users *user)
{
    if(usersCount == 0){
        userRoot = user;
        userLast = user;
        user->setUserId(0);
        usersCount = 1;
    }else{
        userLast->nextUser = user;
        user->previousUser=userLast;
        userLast = user;
        user->setUserId(usersCount);
        usersCount++;
    }
}

/// Add user to the chained list at the position id
bool UsersChain::addUserAt(Users *user,int id)
{
    bool ok = false;
    if(usersCount > id){
        Users *userTmp = userAt(id);
        if(userTmp->previousUser){
            user->previousUser = userTmp->previousUser;
            user->previousUser->nextUser = user;
            userTmp->previousUser = user;
        }
        user->nextUser = userTmp;
        userTmp->previousUser = user;
        user->setUserId(id);
        userTmp->setUserId(id+1);
        while(userTmp->nextUser){
            userTmp = userTmp->nextUser;
            userTmp->setUserId(userTmp->getUserId()+1);
        }
        ok = true;
    }else{
        ok = false;
    }
    return ok;
}

/// Delete a user from the chained list
void UsersChain::deleteUser(Users *user)
{

    Users *userTmp = user;

    if(user == userRoot){
        if(usersCount == 1){
            userRoot = 0;
            userLast = 0;
            userTmp = 0;
        }else{
            userRoot = user->nextUser;
            userRoot->previousUser = 0;
            userTmp = userRoot;
        }
    }else if(user == userLast){
        userLast = user->previousUser;
        userLast->nextUser = 0;
        userTmp = userLast->nextUser;
    }else{
        user->previousUser->nextUser = user->nextUser;
        user->nextUser->previousUser = user->previousUser;
        userTmp = user->nextUser;
    }

    while(userTmp){
        userTmp->setUserId(userTmp->getUserId()-1);
        userTmp = userTmp->nextUser;
    }

    usersCount--;
    delete user;

}

/// Delete a user from the chained list which has index id
void UsersChain::deleteUserAt(int id)
{
    Users *userTmp = userAt(id);
    this->deleteUser(userTmp);
}

/// Get the user that has index id from the chained list
Users *UsersChain::userAt(int id) const
{
    Users *userTmp = userRoot;
    while(userTmp->getUserId() != id){
        userTmp = userTmp->nextUser;
        if(!userTmp)
            return 0;
    }
    return userTmp;
}

/// Get the user that has username and password from chained list
Users *UsersChain::getUser(QString username, QString password) const
{
    Users *userTmp = userRoot;
    bool userExists = false;
    while(userTmp){
        if((userTmp->getPassword() == password) && (userTmp->getUsername() == username)){
            userExists = true;
            break;
        }else{
            userTmp = userTmp->nextUser;
        }
    }

    if (!userExists)
        userTmp = 0;

    return userTmp;
}

/// Check whether a user with username is present in the chained list
bool UsersChain::containsUser(QString username) const
{
    Users *userTmp = userRoot;
    bool contains = false;
    while(userTmp){
        if(userTmp->getUsername() == username){
            contains = true;
            break;
        }else{
            userTmp = userTmp->nextUser;
        }
    }
    return contains;
}

void UsersChain::update(DataBase *database)
{
    for(int i=usersCount-1; i>=0; i--)
        this->deleteUserAt(i);

    Users *user = 0;
    int userNumLines = database->getUserNumlines();
    for(int i=0; i<userNumLines; i++){
        user = database->getUserDb(i);
        this->addUser(user);
    }
}
