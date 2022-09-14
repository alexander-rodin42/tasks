#include <iostream>
#include <functional>
#include <vector>

namespace rav {
    void bubble_sorting(
        std::vector<int>& vector,
        std::function<bool(int, int)> comparator = [](int a, int b) -> bool { return a > b; }) noexcept
    {
        for (size_t i = 0; i < vector.size(); ++i)
        {
            for (size_t j = 0; j < vector.size() - i - 1; ++j)
            {
                if (comparator(vector[j], vector[j + 1]))
                {
                    std::swap(vector[j], vector[j + 1]);
                }
            }
        }
    }

    void print_vector(const std::vector<int>& vector, const std::string& message)
    {
        std::cout << message;
        for (const auto& value : vector)
        {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }

    bool custom_comparator(int a, int b)
    {
        return a < b;
    }

    //----------------------------------------------------------------------------------------------

    template <typename Collection, typename Comparator, typename = typename Collection::size_type>
    void bubble_sorting_template(Collection& collection, Comparator comparator) noexcept
    {
        for (typename Collection::size_type i = 0; i < collection.size(); i++)
        {
            for (typename Collection::size_type j = 0; j < collection.size() - i - 1; j++)
            {
                if (comparator(collection[j], collection[j + 1]))
                {
                    std::swap(collection[j], collection[j + 1]);
                }
            }
        }
    }
}  // namespace rav


int main()
{
    std::vector<int> vector = {7, 9, 1, 5, 8, 1, 8, 3, 7, 3, 4, 1, 9, 2, 3};
    rav::print_vector(vector, "Not sorted array: ");

    rav::bubble_sorting(vector);
    rav::print_vector(vector, "Sorted array: ");

    rav::bubble_sorting(vector, rav::custom_comparator);
    rav::print_vector(vector, "Sorted array: ");

    //----------------------------------------------------------------------------------------------

    rav::bubble_sorting_template(vector, [](int a, int b) -> bool { return a > b; });
    rav::print_vector(vector, "Sorted array: ");

    return EXIT_SUCCESS;
}
