#pragma once 

#include <iostream>
#include "Hash.h"
#include <fstream>
#include "Users.h"


void regist()
{
    system("cls");
    Users newUser = Users();
    std::cout << "Enter a login: ";
    std::string login;
    std::cin >> login;
    std::cout << "Enter your name: ";
    std::string name;
    std::cin >> name;
    std::string pass1, pass2;

    newUser.setLogin(login);
    newUser.setName(name);
    newUser.setStat("user");
    newUser.setMoney(.0f);

    bool isProc{ true };
    while (isProc)
    {
        std::cout << "Enter a password: ";
        std::cin >> pass1;
        std::cout << "Enter a password again: ";
        std::cin >> pass2;
        if (pass1.length() > 4 && pass1 == pass2)
            isProc = false;
        else
            std::cout << "Passwords should be bigger than 4 symbols and equal!\n\n";
    }
    pass1 = myHash::code(pass1);
    newUser.saveUserInFiles(pass1);
}

bool authoriz(std::string login)
{
    system("cls");
    std::cout << "\tAutorization!\n";
    std::cout << "Enter your login: ";
    std::cin >> login;

    std::cout << "Enter your password: ";
    //TODO: make a silent entering
    std::string password;
    std::cin >> password;
    password = myHash::code(password);

    std::ifstream file("Users.txt");

    if (!file)
    {
        std::cout << "Error. File was not found!";
        return false;
    }

    while(file)
    {
        std::string f_login;
        std::string f_pass;
        file >> f_login >> f_pass;
        if (login == f_login && password == f_pass)
        {
            file.close();
            return true;
        }
    }
    std::cout << "Who are you? I don't know you.\n";
    return false;
}