#include <iostream>
#include <vector>

namespace rav {

    template <typename Collection>
    using ValueType = typename Collection::value_type;

    template <typename Collection>
    using SizeType = typename Collection::size_type;

    template <typename Collection>
    int binary_search_template(const Collection& collection, const ValueType<Collection>& value) noexcept
    {
        SizeType<Collection> left = 0u;
        SizeType<Collection> right = collection.size();

        while (left <= right)
        {
            SizeType<Collection> middle = (left + right) / 2;

            if (collection[middle] < value)
            {
                left = middle + 1;
            }
            else if (collection[middle] > value)
            {
                right = middle - 1;
            }
            else
            {
                return static_cast<int>(middle);
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
    std::cout << "The number " << targetValue << " has an index: " << rav::binary_search_template(vector, targetValue)
              << std::endl;

    targetValue = 85;
    std::cout << "The number " << targetValue << " has an index: " << rav::binary_search_template(vector, targetValue)
              << std::endl;

    return EXIT_SUCCESS;
}
