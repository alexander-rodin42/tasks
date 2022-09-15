#include <iostream>
#include <vector>
#include <array>

namespace rav {
    void quick_sort(std::vector<int>& vector, size_t left, size_t right) noexcept
    {
        size_t l = left;
        size_t r = right;
        auto mid = vector[(left + right) / 2];

        while (l <= r)
        {
            while (vector[l] < mid)
            {
                ++l;
            }
            while (vector[r] > mid)
            {
                --r;
            }
            if (l <= r)
            {
                std::swap(vector[l++], vector[r--]);
            }
        }

        if (l < right)
        {
            quick_sort(vector, l, right);
        }
        if (r > left)
        {
            quick_sort(vector, left, r);
        }
    }

    //----------------------------------------------------------------------------------------------

    template <typename Collection, typename Comparator>
    void quick_sort_template(Collection& array, size_t left, size_t right, Comparator comparator)
    {
        size_t l = left;
        size_t r = right;
        auto mid = array[(left + right) / 2];

        while (l <= r)
        {
            while (comparator(mid, array[l]))
            {
                l++;
            }
            while (comparator(array[r], mid))
            {
                r--;
            }
            if (l <= r)
            {
                std::swap(array[l++], array[r--]);
            }
        }

        if (l < right)
        {
            quick_sort_template(array, l, right, comparator);
        }
        if (r > left)
        {
            quick_sort_template(array, left, r, comparator);
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

    rav::quick_sort(vector, 0, vector.size() - 1);
    rav::print_collection(vector, "Sorted vector: ");

    //----------------------------------------------------------------------------------------------

    std::array<int, 15> array = {7, 9, 1, 5, 8, 1, 8, 3, 7, 3, 4, 1, 9, 2, 3};
    rav::print_collection(array, "Not sorted array: ");

    rav::quick_sort_template(array, 0, array.size() - 1, [](int a, int b) -> bool { return a > b; });
    rav::print_collection(array, "Sorted array: ");
    rav::quick_sort_template(array, 0, array.size() - 1, [](int a, int b) -> bool { return a < b; });
    rav::print_collection(array, "Sorted array: ");

    return EXIT_SUCCESS;
}
