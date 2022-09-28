#include <iostream>
#include "Stack.h"
#include "Test.h"

int main(int argc, char* argv[])
{
    try
    {
        // Check exceptions:
        // rav::Stack<int> stack(100000000000);

        {
            rav::Stack<int> stack(10);
            stack.push(1);
            stack.push(5);
            stack.push(23);
            stack.push(42);
            std::cout << "stack.top(): " << stack.top() << " size: " << stack.size() << std::endl;
            stack.pop();
            std::cout << "stack.top(): " << stack.top() << " size: " << stack.size() << std::endl;
            std::cout << "-------------------------------------------" << std::endl;
        }

        {
            rav::Stack<Test> stack1;
            stack1.push(Test(1));
            std::cout << "Reserve N1, current size: " << stack1.size() << std::endl;
            stack1.push(Test(2));
            stack1.push(Test(3));
            std::cout << "Reserve N2, current size: " << stack1.size() << std::endl;
            stack1.push(Test(4));

            std::cout << "-------------------------------------------" << std::endl;
            std::cout << "Move: stack1 -> stack2:" << std::endl;
            rav::Stack<Test> stack2(std::move(stack1));

            std::cout << "-------------------------------------------" << std::endl;
            std::cout << "Copy: stack3 = stack2:" << std::endl;
            rav::Stack<Test> stack3;
            stack3 = stack2;

            std::cout << "-------------------------------------------" << std::endl;
            std::cout << "Pop: stack3:" << std::endl;
            stack3.pop();

            std::cout << "-------------------------------------------" << std::endl;
            std::cout << "Start destroying" << std::endl;
        }
        std::cout << "Complete destroy" << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
