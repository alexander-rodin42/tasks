#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>

namespace rav {

    auto custom_comparator = [](int a, int b) -> bool { return a < b; };

    void merge_sorting(std::vector<int>& vector,
                       size_t begin,
                       size_t end,
                       std::function<bool(int, int)> comparator = custom_comparator)
    {
        if (end - begin < 2)
        {
            return;
        }

        const size_t mid = (begin + end) / 2;
        merge_sorting(vector, begin, mid, comparator);
        merge_sorting(vector, mid, end, comparator);

        std::vector<int> buffer;
        buffer.reserve(end - begin);
        size_t left = begin;
        size_t right = mid;

        while ((left < mid) && (right < end))
        {
            if (comparator(vector.at(left), vector.at(right)))
            {
                buffer.push_back(vector.at(left));
                ++left;
            }
            else
            {
                buffer.push_back(vector.at(right));
                ++right;
            }
        }

        while (left < mid)
        {
            buffer.push_back(vector.at(left));
            ++left;
        }

        while (right < end)
        {
            buffer.push_back(vector.at(right));
            ++right;
        }

        std::copy(buffer.begin(), buffer.end(), vector.begin() + begin);
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

    rav::merge_sorting(vector, 0, vector.size());
    rav::print_collection(vector, "Sorted vector: ");

    return EXIT_SUCCESS;
}
