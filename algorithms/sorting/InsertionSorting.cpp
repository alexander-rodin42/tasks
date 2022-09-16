#include <iostream>
#include <functional>
#include <vector>

namespace rav {

    auto custom_comparator = [](int a, int b) -> bool { return a < b; };

    void insertion_sorting(std::vector<int>& vector, std::function<bool(int, int)> comparator = custom_comparator) noexcept
    {
        for (int i = 1; i < vector.size(); ++i)
        {
            for (int j = i; (j > 0) && comparator(vector[j], vector[j - 1]); --j)
            {
                std::swap(vector[j], vector[j - 1]);
            }
        }
    }

    //----------------------------------------------------------------------------------------------

    template <typename Collection, typename Comparator>
    void insertion_sorting_template(Collection& collection, Comparator comparator) noexcept
    {
        for (auto i = 1; i < collection.size(); i++)
            for (auto j = i; (j > 0) && (comparator(collection[j], collection[j - 1])); j--)
                std::swap(collection[j], collection[j - 1]);
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

    rav::insertion_sorting(vector);
    rav::print_collection(vector, "Sorted vector: ");

    //----------------------------------------------------------------------------------------------

    rav::insertion_sorting_template(vector, [](int a, int b) -> bool { return a > b; });
    rav::print_collection(vector, "Sorted vector: ");

    return EXIT_SUCCESS;
}
