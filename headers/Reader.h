#pragma once

#include <fstream>
#include <ostream>
#include <iostream>
#include "Items.h"

int getLength(std::string fName)
{
    std::ifstream rFile(fName);
    int size{ 0 };
    while (rFile)
    {
        std::string strOutput;
        rFile >> strOutput;
        if(strOutput == "#")
            size++;
    }
    rFile.close();
    return size;
}

Items* readFileInList(std::string fileName)
{
    std::ifstream rFile(fileName);

    if (!rFile)
    {
        Items* errItem = new Items[1];
        errItem[0].setName("ERROR");
        errItem[0].setPrice(.0f);
        errItem[0].setCount(0);

        return errItem;
    }
    
    int size = getLength(fileName);
    Items* list = new Items[size];

    for (int i = 0; i < size || rFile; ++i)
    {
        std::string strOut;
        rFile >> strOut;
        if(strOut == "#")
        {
            std::string name;
            float price;
            int count;
            rFile >> name >> price >> count;
            list[i].setName(name);
            list[i].setPrice(price);
            list[i].setCount(count);
        }
    }

    rFile.close();
    return list;
}

void writeListInFile(Items* items, int size, std::string fileName)
{
    std::ofstream file(fileName);
    if (file)
    {
        for (int i = 0; i < size; ++i)
            file << "# " << items[i].getName() 
                 << " "  << items[i].getPrice() 
                 << " "  << items[i].getCount() << "\n";
        std::cout << "File was rewrited successful!\n";
    }
    else
    {
        std::cout << "Error. File was not open!\n";
    }
    file.close();
}
