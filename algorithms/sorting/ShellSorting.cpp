#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>

namespace rav {

    auto custom_comparator = [](int a, int b) -> bool { return a < b; };

    void shell_sorting(std::vector<int>& vector, std::function<bool(int, int)> comparator = custom_comparator)
    {
        for (size_t step = vector.size() / 2; step > 0; step /= 2)
        {
            for (size_t i = step; i < vector.size(); ++i)
            {
                for (size_t j = i; (j > step - 1) && comparator(vector[j], vector[j - step]); --j)
                {
                    std::swap(vector[j], vector[j - step]);
                }
            }
        }
    }

    //----------------------------------------------------------------------------------------------

    template <typename Collection, typename Comparator, typename = typename Collection::iterator>
    void shell_sorting_template(Collection& collection, Comparator comparator) noexcept
    {
        for (typename Collection::size_type step = collection.size() / 2; step > 0; step /= 2)
        {
            for (typename Collection::size_type i = step; i < collection.size(); i++)
            {
                for (typename Collection::size_type j = i; (j > step - 1) && comparator(collection[j], collection[j - step]);
                     j--)
                {
                    std::swap(collection[j], collection[j - step]);
                }
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

    rav::shell_sorting(vector);
    rav::print_collection(vector, "Sorted vector: ");

    rav::shell_sorting_template(vector, [](int a, int b) -> bool { return a > b; });
    rav::print_collection(vector, "Sorted vector: ");

    return EXIT_SUCCESS;
}
