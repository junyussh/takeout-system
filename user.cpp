#include"user.h"

User::User(string name, string card, string password)
{
    this->name = name;
    this->card = card;
    this->password = password;
}

User::~User()
{
}
