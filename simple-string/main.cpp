#include <iostream>
#include <algorithm>
#include <vector>

#include "SimpleString.h"

using namespace rav;

std::istream& operator>>(std::istream& is, SimpleString& simpleString)
{
    std::string inData;
    is >> inData;
    if (is)
    {
        simpleString = inData.c_str();
    }

    return is;
}

std::ostream& operator<<(std::ostream& os, const SimpleString& string)
{
    return os << string.data();
}


void input(std::vector<SimpleString>& vector)
{
    std::cout << "To finish entering words, enter \"stop\"" << std::endl;

    SimpleString input;
    while (input != "stop")
    {
        std::cout << "Enter a word: ";
        std::cin >> input;

        if (input != "stop")
        {
            vector.push_back(input);
        }
    }
}

void convertToLowercase(SimpleString& value)
{
    for (size_t i = 0; i < value.size(); ++i)
    {
        if (value[i] >= 'A' && value[i] <= 'Z')
        {
            value[i] += 32;
        }
    }
}

void printInfo(const std::vector<SimpleString>& vector)
{
    for (auto& i : vector)
    {
        std::cout << i << std::endl;
    }
}

auto compareSymbols = [](SimpleString first, SimpleString second) {
    convertToLowercase(first);
    convertToLowercase(second);
    return first > second;
};

int main(int argc, char* argv[])
{
    std::vector<SimpleString> data = {"abc", "BCD", "ABC", "123", "bcd", "aBC"};
    std::cout << "Not sorted vector:" << std::endl;
    printInfo(data);
    std::sort(data.begin(), data.end(), compareSymbols);
    std::cout << "Sorted vector:" << std::endl;
    printInfo(data);

    //-------------------------------------------------------------------------------------
    std::vector<SimpleString> inData;
    input(inData);
    std::sort(inData.begin(), inData.end(), compareSymbols);
    printInfo(inData);

    //-------------------------------------------------------------------------------------
    SimpleString command;
    while (command != "exit")
    {
        std::cout << "Enter \"exit\": ";
        std::cin >> command;
    }

    return EXIT_SUCCESS;
}
