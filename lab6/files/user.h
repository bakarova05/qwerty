#pragma once
#include <string>

class user
{
    public:
    user();
    user(std::string Name);
    std::string getName();
    void setName(std::string Name);
    private:
    std::string name;
};