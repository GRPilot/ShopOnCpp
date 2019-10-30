#pragma once 

#include <iostream>
#include <string>

using namespace std;

namespace myHash
{
    class Hash
    {
        string hash;
        int receivingExistCodes(int x);
        int getControlSum(string str);

    public:
        string getHash(string userString, unsigned int lengthHash);
    };

    int Hash::receivingExistCodes(int x)
    {
        x += 256;
        while(!(
                ((x <= 57)  && (x >= 48)) || 
                ((x <= 90)  && (x >= 65)) || 
                ((x <= 122) || (x >= 97))
                )
             )
        {
            if (x < 48)
                x += 24;
            else
                x -= 47;
        }
        return x;
    }
    int Hash::getControlSum(string str)
    {
        unsigned int sault{}, strlen{};

        for (; strlen < str.size(); strlen++)
            sault += int(str[strlen]);

        return sault;
    }
    string Hash::getHash(string userString, unsigned int lengthHash)
    {
        if(lengthHash > 3)
        {
            unsigned int minLen{ 2 };
            unsigned int realMinLen{};

            unsigned int originalSault = this->getControlSum(userString);
            unsigned int originalLenghtStr = (userString.size());

            while (minLen <= lengthHash)
                realMinLen = (minLen *= 2);
            
            while (minLen < originalLenghtStr)
                realMinLen *= 2;

            if ((minLen - originalLenghtStr) < minLen)
                minLen *= 2;

            int addCount = minLen - originalLenghtStr;

            for (int i = 0; i < addCount; i++)
                userString += this->receivingExistCodes(userString[i] + userString[i + 1]);
            
            int maxSault = this->getControlSum(userString);
            int maxLenghtStr = (userString.size());

            while (userString.size() != realMinLen)
            {
                for (int i{}, center = userString.size() / 2; i < center; i++)
                    this->hash += this->receivingExistCodes(userString[center - i] + userString[center + i]);
                
                userString = this->hash;
                this->hash.clear();
            }

            unsigned int rem = realMinLen - lengthHash;

            for (unsigned int i{}, countCompress = realMinLen / rem; this->hash.size() < (lengthHash - 4); i++)
            {
                if (i % countCompress == 0)
                    this->hash += this->receivingExistCodes(userString[i] + userString[++i]);
                else
                    this->hash += userString[i];
            }

            this->hash += this->receivingExistCodes(originalSault);
            this->hash += this->receivingExistCodes(originalLenghtStr);

            this->hash += this->receivingExistCodes(maxSault);
            this->hash += this->receivingExistCodes(maxLenghtStr);

            return this->hash;
        }
        return "";
    }

    std::string code(std::string pass)
    {
        const int key = 5;
        myHash::Hash creatHash;
        pass = creatHash.getHash(pass, key);
        return pass;
    }
}