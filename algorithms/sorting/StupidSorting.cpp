#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>

namespace rav {

    auto custom_comparator = [](int a, int b) -> bool { return a < b; };

    void stupid_sorting(std::vector<int>& vector, std::function<bool(int, int)> comparator = custom_comparator)
    {
        for (size_t i = 0; i < vector.size() - 1; ++i)
        {
            if (comparator(vector[i + 1], vector[i]))
            {
                std::swap(vector[i + 1], vector[i]);
                i = -1;
            }
        }
    }

    //----------------------------------------------------------------------------------------------

    template <typename Collection, typename Comparator, typename = typename Collection::iterator>
    void stupid_sorting_template(Collection& collection, Comparator comparator) noexcept
    {
        for (typename Collection::size_type i = 0; i < collection.size() - 1; ++i)
        {
            if (comparator(collection[i + 1], collection[i]))
            {
                std::swap(collection[i + 1], collection[i]);
                i = -1;
            }
        }
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
    std::vector<int> vector = {7, 9, 1, 5, 8, 1, 8, 3, 7, 3, 4, 1, 9, 2, 3};
    rav::print_collection(vector, "Not sorted vector: ");

    rav::stupid_sorting(vector);
    rav::print_collection(vector, "Sorted vector: ");

    rav::stupid_sorting_template(vector, [](int a, int b) -> bool { return a > b; });
    rav::print_collection(vector, "Sorted vector: ");

    return EXIT_SUCCESS;
}
