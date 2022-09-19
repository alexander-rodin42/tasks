#include <iostream>
#include <vector>

namespace rav {

    template <typename Collection>
    using ValueType = typename Collection::value_type;

    template <typename Collection>
    using SizeType = typename Collection::size_type;

    template <typename Collection>
    int linear_search(const Collection& collection, const ValueType<Collection>& value) noexcept
    {
        for (SizeType<Collection> i = 0; i < collection.size(); ++i)
        {
            if (collection[i] == value)
            {
                return i;
            }
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
    std::cout << "The number " << targetValue << " has an index: " << rav::linear_search(vector, targetValue) << std::endl;

    targetValue = 85;
    std::cout << "The number " << targetValue << " has an index: " << rav::linear_search(vector, targetValue) << std::endl;

    return EXIT_SUCCESS;
}
