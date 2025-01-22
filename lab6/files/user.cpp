#include "user.h"

user::user(){};

user::user(std::string Name)
{
    name = Name;
};

std::string user::getName()
{
    return name;
};

void user::setName(std::string Name)
{
    name = Name;
};