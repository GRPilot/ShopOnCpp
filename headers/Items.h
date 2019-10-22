#pragma once

#include <iostream>

class Items
{
private:
    std::string name;
    float price;
    int count;

public:
    Items(std::string outName, float outPrice, int outCount);
    Items();

    std::string getName();
    float getPrice();
    int getCount();

    void setName(std::string outName);
    void setPrice(float outPrice);
    void setCount(int outCount);

    ~Items();
};

Items::Items()
{

}
Items::Items(std::string outName, float outPrice, int outCount)
{
    name = outName;
    price = outPrice;
    count = outCount;
}
Items::~Items(){}

std::string Items::getName()
{
    return name;
}

float Items::getPrice()
{
    return price;
}

int Items::getCount()
{
    return count;
}

void Items::setName(std::string outName)
{
    name = outName;
}
void Items::setPrice(float outPrice)
{
    price = outPrice;
}
void Items::setCount(int outCount)
{
    count = outCount;
}