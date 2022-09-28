#pragma once

class Test
{
public:
    Test();
    Test(const int inValue);
    Test(const Test& other);
    Test& operator=(const Test& other);
    ~Test();

private:
    int x = 0;
    static size_t objectCount;
};
