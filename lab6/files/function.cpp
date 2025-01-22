#include "doc.h"
#include "function.h"
#include "user.h"
#include <iostream>

controler::controler(){};

void controler::start()
{
    doc d;
    int answer1;
    std::string answer2;
    bool triger = 1;
    std::cout << "1. create file\n2. import file\n3. exit\n";
    std::cin >> answer1;

    if (answer1 == 2)
    {
        std::cout << "enter the path: ";
        std::cin >> answer2;
        doc d(answer2);
    }

    if (answer1 == 3)
    {
        triger = 0;
    }

    while (triger)
    {

        std::cout << "\n\n1. add user\n2. del user\n3. get list of users\n4. export file\n5. exit\n";
        std::cin >> answer1;

        if (answer1 == 1)
        {
            std::string name;
            std::cout << "enter user name: ";
            std::cin >> name;
        }
        else if (answer1 == 2)
        {
            d.delUser();
        }
        else if (answer1 == 3)
        {
            d.getUser();
        }
        else if (answer1 == 4)
        {
            std::cout << "Enter the path: ";
            std::cin >> answer2;
            d.exportDoc(answer2);
        }
        else if (answer1 == 5)
        {
            triger = 0;
        }
    }
    return;
};