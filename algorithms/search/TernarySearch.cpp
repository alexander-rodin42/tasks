#include <iostream>
#include <vector>

namespace rav {

    int ternary_search(const std::vector<int>& data, const int left, const int right, const int value)
    {
        const int mid1 = left + (right - left) / 3;
        const int mid2 = right - (right - left) / 3;

        if (data[mid1] == value)
        {
            return mid1;
        }

        if (data[mid2] == value)
        {
            return mid2;
        }

        if (value < data[mid1])
        {
            return ternary_search(data, left, mid1 - 1, value);
        }
        else if (value > data[mid2])
        {
            return ternary_search(data, mid2 + 1, right, value);
        }
        else
        {
            return ternary_search(data, mid1 + 1, mid2 - 1, value);
        }

        return -1;
    }

    //----------------------------------------------------------------------------------------------

    template <typename Collection>
    void print_collection(const Collection& collection, const std::string& message)
    {
        std::cout << message;
        for (const auto& value : collection)
        {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }

}  // namespace rav

int main()
{
    //                         0  1  2   3   4   5   6   7   8   9   10  11   12   13
    std::vector<int> vector = {1, 8, 12, 15, 25, 32, 42, 56, 74, 85, 90, 114, 123, 95};
    rav::print_collection(vector, "Vector: ");

    int targetValue = 15;
    std::cout << "The number " << targetValue
              << " has an index: " << rav::ternary_search(vector, 0u, vector.size() - 1, targetValue) << std::endl;

    targetValue = 85;
    std::cout << "The number " << targetValue
              << " has an index: " << rav::ternary_search(vector, 0u, vector.size() - 1, targetValue) << std::endl;

    return EXIT_SUCCESS;
}
