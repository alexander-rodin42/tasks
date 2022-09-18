#include <iostream>
#include <functional>
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
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "Fill array. To finish entering words, enter \"stop\"." << std::endl;

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
    std::cout << "---------------------------------------------------" << std::endl;
}

void printInfo(const std::vector<SimpleString>& vector)
{
    for (auto& i : vector)
    {
        std::cout << i << std::endl;
    }
}

auto compareSymbols = [](SimpleString first, SimpleString second) -> bool {
    std::transform(first.begin(), first.end(), first.begin(), ::tolower);
    std::transform(second.begin(), second.end(), second.begin(), ::tolower);
    return first > second;
};

int main(int argc, char* argv[])
{
    // Example:
    std::vector<SimpleString> data{"abc", "BCD", "ABC", "123", "bcd", "aBC"};
    std::cout << "Sorting example:" << std::endl;
    std::cout << "Not sorted vector:" << std::endl;
    printInfo(data);
    std::sort(data.begin(), data.end(), compareSymbols);
    std::cout << "Sorted vector:" << std::endl;
    printInfo(data);

    //------------------------------------------------------------------------------
    std::vector<SimpleString> inData;
    input(inData);
    std::sort(inData.begin(), inData.end(), compareSymbols);
    printInfo(inData);

    //------------------------------------------------------------------------------
    std::cout << "---------------------------------------------------" << std::endl;
    SimpleString command;
    while (command != "exit")
    {
        std::cout << "Enter \"exit\": ";
        std::cin >> command;
    }

    return EXIT_SUCCESS;
}
