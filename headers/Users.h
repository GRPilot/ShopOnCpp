#pragma once

#include <iostream>
#include <fstream>
#include <map>

const std::string g_fUsers = "Users.txt";
const std::string g_fUsersInfo = "UserInfo.txt";

int getNumberOfUsers()
{
    std::ifstream file(g_fUsersInfo);
    int count{};
    while (file)
    {
        std::string buff;
        file >> buff;
        if (buff == "#")
            count++;
    }
    file.close();
    return count;
}

class Users
{
private:
    std::string Login, oldLogin;
    std::string Name;
    std::string status;
    float money;
    
public:
    Users(std::string outLogin);
    Users();
    ~Users();

    std::string GetLogin() { return Login; }
    std::string GetName()  { return Name; }
    std::string GetStat()  { return status; }
    float       GetMoney() { return money; }

    void setLogin(std::string outLogin);
    void setName(std::string outName)   { Name = outName; }
    void setStat(std::string outStatus) { status = outStatus; }
    void setMoney(float outMoney)       { money = outMoney; }

    void rewriteUserInfo();
    void saveUserInFiles(std::string pass);
};

Users::Users(){}

Users::Users(std::string outLogin)
{
    std::ifstream file(g_fUsersInfo);
    std::string LoginFromFile = "";
    
    while (file && outLogin != LoginFromFile)
    {
        file >> LoginFromFile;
    }
    if (!file.eof())
    {
        Login = outLogin;
        oldLogin = outLogin;
        file >> LoginFromFile;
        file >> status;
        file >> LoginFromFile;
        file >> Name;
        file >> LoginFromFile;
        file >> money;
    }
    else
    {
        std::cout << "Error. User not found!\n";
        Login = "noname";
        Name = "\%USERNAME%";
        status = "non-registered";
        money = .0f;
    }
    
}

Users::~Users(){}

void Users::saveUserInFiles(std::string pass)
{
    std::ofstream usersFile(g_fUsers, std::ios::app);
    usersFile << std::endl << Login << " " << pass;
    usersFile.close();

    std::ofstream usersInfo(g_fUsersInfo, std::ios::app);
    usersInfo << std::endl;
    usersInfo << "# " << Login << std::endl;
    usersInfo << "Status: " << status << std::endl;
    usersInfo << "Name: " << Name << std::endl;
    usersInfo << "Money " << money << std::endl;
    usersInfo.close();
}

void Users::rewriteUserInfo()
{
    std::ifstream mainFile(g_fUsersInfo);
    int size = getNumberOfUsers();
    Users* list = new Users[size];
    for (int i = 0; i < size && mainFile; ++i)
    {
        std::string buff = "";
        float money{};
            
        mainFile >> buff >> buff;
        list[i].setLogin(buff);
        mainFile >> buff >> buff;
        list[i].setStat(buff);
        mainFile >> buff >> buff;
        list[i].setName(buff);
        mainFile >> buff >> money;
        list[i].setMoney(money);
    }
    mainFile.close();

    for (int i = 0; i < size; ++i)
    {
        if (list[i].GetLogin() == oldLogin)
        {
            list[i].setLogin(Login);
            list[i].setName(Name);
            list[i].setStat(status);
            list[i].setMoney(money);
            break;
        }
    }

    std::ofstream buffFile(g_fUsersInfo, std::ios::trunc);
    for (int i = 0; i < size; i++)
    {
        buffFile << "# "<< list[i].GetLogin() << std::endl;
        buffFile << "Status: " << list[i].GetStat() << std::endl;
        buffFile << "Name: " << list[i].GetName() << std::endl;
        buffFile << "Money: " << list[i].GetMoney() << std::endl;
    }
    buffFile.close();
}

void Users::setLogin(std::string outLogin)
{
    bool saveIt{ false };
    std::ifstream file(g_fUsers);
    const int size = getNumberOfUsers();
    std::string *buffLog = new std::string[size], 
                *buffPass = new std::string[size];

    for (int i = 0; i < size && file; i++)
    {
        file >> buffLog[i];
        file >> buffPass[i];
    }

    for (int i = 0; i < size; ++i)
        if(buffLog[i] == Login)
        {
            saveIt = true;
            buffLog[i] = outLogin;
            break;
        }
    file.close();
    Login = outLogin;
    if(saveIt)
    {
        std::ofstream rewriteFile(g_fUsers, std::ios::trunc);
        for(int i = 0; i < size; i++)
            rewriteFile << buffLog[i] << " " << buffPass[i] << std::endl;
        
        rewriteFile.close();
    }
    delete [] buffLog;
    delete [] buffPass;  
}