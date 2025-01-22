#include "doc.h"
#include <iostream>

doc::doc(){};

doc::doc(std::string path)
{
    std::cout << "import from " << path << std::endl;
};

void doc::addUser(user User)
{
    users.push_back(User);
    std::cout << "added user " << User.getName() << std::endl;
};

std::vector<user> doc::getUser()
{
    std::cout << "users:" << std:: endl;
    for(int i = 0; i < users.size(); i++)
    {
        std::cout << "  " << users[i].getName() << std::endl;
    }
    return users;
};

void doc::delUser()
{
    std::cout << "deleted object " << users[users.size() - 1].getName() << std::endl;
    users.pop_back();
};

void doc::exportDoc(std::string path)
{
    std::cout << "the file has been exported to " << path << std::endl;
};