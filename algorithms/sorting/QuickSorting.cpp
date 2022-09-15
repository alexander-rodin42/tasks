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

    template <typename Collection>
    void quick_sort_template(Collection& array, size_t left, size_t right)
    {
        size_t l = left;
        size_t r = right;
        auto key = array[(left + right) / 2];

        while (l <= r)
        {
            while (array[l] < key)
            {
                l++;
            }
            while (array[r] > key)
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
            quick_sort_template(array, l, right);
        }
        if (r > left)
        {
            quick_sort_template(array, left, r);
        }
    }

    //----------------------------------------------------------------------------------------------

    template <typename Collection>
    void print_array(const Collection& array, const std::string& message)
    {
        std::cout << message;
        for (auto& value : array)
        {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }

}  // namespace rav

int main()
{
    std::vector<int> vector = {7, 9, 1, 5, 8, 1, 8, 3, 7, 3, 4, 1, 9, 2, 3};
    rav::print_array(vector, "Not sorted vector: ");

    rav::quick_sort(vector, 0, vector.size() - 1);
    rav::print_array(vector, "Sorted vector: ");

    //----------------------------------------------------------------------------------------------

    std::array<int, 15> array = {7, 9, 1, 5, 8, 1, 8, 3, 7, 3, 4, 1, 9, 2, 3};
    rav::print_array(array, "Not sorted array: ");

    rav::quick_sort_template(array, 0, array.size() - 1);
    rav::print_array(array, "Sorted array: ");

    return EXIT_SUCCESS;
}
