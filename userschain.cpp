#include "userschain.h"

UsersChain::UsersChain()
{
    usersCount = 0;
    userRoot = 0;
    userLast = 0;
}

void UsersChain::addUser(Users *user)
{
    if(usersCount == 0){
        userRoot = user;
        userLast = user;
        usersCount = 1;
    }else{
        userLast->nextUser = user;
        user->previousUser=userLast;
        userLast = user;
        user->setId(usersCount);
        usersCount++;
    }
}

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
        user->setId(id);
        userTmp->setId(id+1);
        while(userTmp->nextUser){
            userTmp = userTmp->nextUser;
            userTmp->setId(userTmp->getId()+1);
        }
        ok = true;
    }else{
        ok = false;
    }
    return ok;
}

void UsersChain::deleteUser(Users *user)
{
    Users *userTmp = user;

    user->previousUser->nextUser = user->nextUser;
    user->nextUser->previousUser = user->previousUser;

    while(userTmp){
        userTmp->nextUser->setId(userTmp->nextUser->getId()-1);
        userTmp = userTmp->nextUser;
    }

    usersCount--;
    delete user;
}

void UsersChain::deleteUserAt(int id)
{
    Users *userTmp = userAt(id);
    this->deleteUser(userTmp);
}

Users *UsersChain::userAt(int id) const
{
    Users *userTmp = userRoot;
    while(userTmp->getId() != id){
        userTmp = userTmp->nextUser;
        if(!userTmp)
            return 0;
    }
    return userTmp;
}

Users *UsersChain::getUser(QString username, QString password) const
{
    Users *userTmp = userRoot;
    while(userTmp){
        if((userTmp->getPassword() == password) && (userTmp->getUsername() == username)){
            break;
        }else{
            userTmp = userTmp->nextUser;
        }
    }
    return userTmp;
}

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
