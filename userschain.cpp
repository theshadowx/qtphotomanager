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

void UsersChain::deleteUserAt(int id)
{
    Users *userTmp = userAt(id);
    this->deleteUser(userTmp);
}

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
