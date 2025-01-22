#pragma once
#include "user.h"
#include <vector>

class doc
{
    public:
    doc();
    doc(std::string path);
    void addUser(user User);
    void delUser();
    void exportDoc(std::string path);
    std::vector<user> getUser();
    private:
    std::vector<user> users;
};