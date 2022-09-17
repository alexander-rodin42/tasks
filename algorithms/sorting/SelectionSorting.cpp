#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>

namespace rav {

    auto custom_comparator = [](int a, int b) -> bool { return a < b; };

    void selection_sorting(std::vector<int>& vector, std::function<bool(int, int)> comparator = custom_comparator)
    {
        for (int i = 0; i < vector.size(); ++i)
        {
            size_t elementIndex = i;

            for (int j = i + 1; j < vector.size(); ++j)
            {
                if (comparator(vector[j], vector[elementIndex]))
                {
                    elementIndex = j;
                }
            }

            if (i != elementIndex)
            {
                std::swap(vector[i], vector[elementIndex]);
            }
        }
    }

    //----------------------------------------------------------------------------------------------

    template <typename Collection, typename Comparator, typename = typename Collection::iterator>
    void selection_sorting_template(Collection& collection, Comparator comparator) noexcept
    {
        for (typename Collection::size_type i = 0; i < collection.size() - 1; i++)
        {
            typename Collection::size_type key_element_index = i;
            for (typename Collection::size_type j = i + 1; j < collection.size(); j++)
                if (comparator(collection[j], collection[key_element_index]))
                    key_element_index = j;

            if (key_element_index != i)
                std::swap(collection[i], collection[key_element_index]);
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

    rav::selection_sorting(vector);
    rav::print_collection(vector, "Sorted vector: ");

    return EXIT_SUCCESS;
}
