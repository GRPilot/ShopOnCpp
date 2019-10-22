#include <iostream>
#include <Windows.h>
#include <string>
#include "headers/Reader.h"
#include "headers/Authorization.h"
#include "headers/Items.h"
#include "headers/Users.h"

#define cWhite SetConsoleTextAttribute(hConsole, (WORD)7)
#define cRed SetConsoleTextAttribute(hConsole, (WORD)4)

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void showList(Items* items, int size);
void GetItem(Users &user);
void Profile(Users &user);
void editProfile(Users &user);
void showInfo(Users user);
bool menu(Users &user);

int main()
{
    std::string login;
    bool isAuthoriz{ true };
    bool isProcMenu{ true };

    while (isAuthoriz)
    {
        system("cls");
        std::cout << "\tAuthorization\n";
        std::cout << "If you didn't sign up, enter ";
        cRed; 
        std::cout << "'sign up'"; 
        cWhite;
        std::cout << ".\n" << "If you already have acount, enter ";
        cRed;
        std::cout << "'log in'"; 
        cWhite;
        std::cout << "Or you can leave. Enter ";
        cRed;
        std::cout << "'exit'"; 
        cWhite;
        std::cout << " for it.\n\n>> ";

        std::string choise;
        std::getline(std::cin, choise, '\n');
        std::cin.clear();

        if(choise == "Log in" || choise == "log in" ||
           choise == "Login"  || choise == "login")
        {
            isAuthoriz = !authoriz(login);
        }
        else if (choise == "sign up" || choise == "Sign up" ||
                 choise == "signup"  || choise == "Signup")
        {
            regist();
        }
        else if (choise == "exit" || choise == "Exit")
        {    isProcMenu = false; isAuthoriz = false; }

        
    }
    system("cls");

    Users user = Users(login);
    
    while (isProcMenu)
    {
        isProcMenu = menu(user);
    }
    
    system("pause");
}

void GetItem(Users &user)
{
    std::string fName = "products.txt";
    Items* list = readFileInList(fName);
    int size = getLength(fName);

    bool isChoising{ true };
    int id, quantity;

    while (isChoising)
    {
        std::cout << "Choise a product:\n";
        showList(list, size);
        std::cout << "Your balance: " << user.GetMoney() << "\n";
        std::cout << "\nEnter an index and quantity ('-1' for back): ";

        bool isEntered{ true };
        bool wasBuy{ false };

        while (isEntered)
        {
            std::cin >> id;
            if (id == -1)
            {
                isEntered = false;
                isChoising = false;
            }
            else 
            {
                std::cin >> quantity;
                id--;
                if (id < 0 || id > size)
                    std::cout << "Invalid id!\n";
                else if (quantity > list[id].getCount())
                    std::cout << "Invalid quantity!\n";
                else if (user.GetMoney() < quantity * list[id].getPrice())
                    std::cout << "You don't have anough money!\n";
                else
                {
                    isEntered = false;
                    wasBuy = true;
                }
            }
        }

        if (wasBuy)
        {
            list[id].setCount(list[id].getCount() - quantity);
            user.setMoney(user.GetMoney() - quantity * list[id].getPrice());
            std::cout << "You have successfully purchased the product. Do you want to buy anything else?\n";
            std::string YesOrNo;
            std::cin >> YesOrNo;

            if (YesOrNo == "no" || YesOrNo == "No")
                isChoising = false;
        }

        system("cls");   
    }
    writeListInFile(list, size, fName); 
}

void showInfo(Users user)
{
    std::cout << "\tYour data:\n";
    std::cout << "Login:\t" << user.GetLogin() << "\n"
              << "Name:\t" << user.GetName() << "\n"
              << "Status:\t" << user.GetStat() << "\n"
              << "Balance:\t" << user.GetMoney() << "\n\n";

}

void editProfile(Users &user)
{
    bool isProc{ true };
    while (isProc)
    {
        system("cls");
        showInfo(user);

        std::cout << "Enter ";
        cRed;
        std::cout << "'Login'";
        cWhite;;
        std::cout << " for change your login.\n";
        std::cout << "Enter ";
        cRed;
        std::cout << "'Name'";
        cWhite;
        std::cout << " for change your name.\n";
        std::cout << "Enter ";
        cRed;
        std::cout << "'Balance'";
        cWhite;
        std::cout << " for change your balance.\n";
        std::cout << "Enter ";
        cRed;
        std::cout << "'Back'";
        cWhite;
        std::cout << " for back.\n";
        std::string choise;
        std::cout << ">> ";
        std::cin >> choise;

        if (choise == "Login" || choise == "login")
        {
            std::string login;
            std::cout << "Enter a new login: ";
            std::cin >> login;
            user.setLogin(login);
            user.rewriteUserInfo();
        }
        else if (choise == "Name" || choise == "name")
        {
            std::string name;
            std::cout << "Enter a new name: ";
            std::cin >> name;
            user.setName(name);
        }
        else if (choise == "balance" || choise == "Balance")
        {
            float balance;
            std::cout << "Enter a new balance: ";
            std::cin >> balance;
            user.setMoney(balance);
        }
        else if (choise == "Back" || choise == "back")
            isProc = false;
    }
}
void Profile(Users &user)
{
    bool isProc{ true };
    while (isProc)
    {
        showInfo(user);

        std::cout << "If you want to change anything, please, enter ";
        cRed;
        std::cout << "'Edit'\n";
        cWhite;
        std::cout << "If you want to change your password, please, enter ";
        cRed;
        std::cout << "'pass'\n";
        cWhite;
        std::cout << "if you want to back to main menu, please, enter ";
        cRed;
        std::cout << "'Back'\n";
        cWhite;
        
        std::cout << ">> ";
        std::string choise;
        std::cin >> choise;
        
        if(choise == "edit" || choise == "Edit")
            editProfile(user);
        else if(choise == "pass" || choise == "Pass")
            std::cout << "editing";                    // edit pass
        else if(choise == "back" || choise == "Back");
            isProc = false;

    }
    system("cls");
}

void showList(Items* items, int size)
{
    std::cout << "----------------------\n";
    for (int i = 0; i < size; ++i)
    {
        SetConsoleTextAttribute(hConsole, (WORD)9);
        std::cout << i + 1 << ". ";
        SetConsoleTextAttribute(hConsole, (WORD)5);
        std::cout << items[i].getName() << "\t- ";
        cRed;
        std::cout << items[i].getPrice();
        SetConsoleTextAttribute(hConsole, (WORD)14);
        std::cout << "$  (" << items[i].getCount() << ")\n";
    }
    cWhite;
    std::cout << "----------------------\n";
}

bool menu(Users &user)
{
    std::cout << "Welcome to the book shop!\n";
    std::cout << "1 - Show books\n"
              << "2 - User Profile\n"
              << "3 - Exit\n";
    std::cout << ">> ";
    int choise;
    std::cin >> choise;
    switch (choise)
    {
    case 1:
        system("cls");
        GetItem(user);
        break;
    case 2:
        system("cls");
        Profile(user);
        break;
    case 3:
        return false;
    
    default:
        system("cls");
        std::cout << "Invalide variable!\n";
        break;
    }
    
    return true;
}