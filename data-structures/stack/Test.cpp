#include "Test.h"

#include <iostream>

size_t Test::objectCount = 0;

Test::Test()
{
    ++objectCount;
    std::cout << "[Object count: " << objectCount << "] Create Test(), x: " << x << std::endl;
}

Test::Test(const int inValue) : x(inValue)
{
    ++objectCount;
    std::cout << "[Object count: " << objectCount << "] Create Test(inValue), x: " << x << std::endl;
}

Test::Test(const Test& other) : x(other.x)
{
    ++objectCount;
    std::cout << "[Object count: " << objectCount << "] Copy Test(other), x: " << x << std::endl;
}

Test& Test::operator=(const Test& other)
{
    if (this == &other)
    {
        return *this;
    }

    x = other.x;
    std::cout << "Copy operator=(other), x: " << x << std::endl;

    return *this;
}

Test::~Test()
{
    --objectCount;
    std::cout << "[Object count: " << objectCount << "] Destroy ~Test(), x: " << x << std::endl;
}
