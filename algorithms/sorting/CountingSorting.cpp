#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>

namespace rav {
    void counting_sorting(std::vector<int>& vector)
    {
        if (vector.empty())
        {
            return;
        }

        auto compare = [](const int l, const int r) -> bool { return l < r; };
        auto minMax = std::minmax_element(vector.begin(), vector.end(), compare);
        auto min = *minMax.first;
        auto max = *minMax.second;

        if (min == max)
        {
            return;
        }

        std::vector<size_t> count(max - min + 1);

        if (min > 0)
        {
            for_each(vector.begin(), vector.end(), [&count, &min](int x) { ++count[x - static_cast<size_t>(min)]; });
        }
        else
        {
            for_each(vector.begin(), vector.end(),
                     [&count, &min](int x) { ++count[x + static_cast<size_t>(std::abs(min))]; });
        }

        vector.clear();
        for (int i = 0; i < count.size(); ++i)
        {
            while (count[i] > 0)
            {
                vector.push_back(i + min);
                --count[i];
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
    std::vector<int> vector = {7, 9, 1, 5, 8, 0, 8, 3, 7, 3, 4, 1, 9, 2, 3};
    rav::print_collection(vector, "Not sorted vector: ");

    rav::counting_sorting(vector);
    rav::print_collection(vector, "Sorted vector: ");

    //----------------------------------------------------------------------------------------------

    std::vector<int> vector2 = {3, 9, -1, 5, 6, 1, 8, -3, 4, 3, -4, 0, -2, 2, 7};
    rav::print_collection(vector2, "Not sorted vector2: ");

    rav::counting_sorting(vector2);
    rav::print_collection(vector2, "Sorted vector2: ");

    //----------------------------------------------------------------------------------------------

    std::vector<int> vector3 = {-3, -9, -1, -5, -6, -1, -8, -3, -4, -3, -4, -1, -2, -2, -7};
    rav::print_collection(vector3, "Not sorted vector3: ");

    rav::counting_sorting(vector3);
    rav::print_collection(vector3, "Sorted vector2: ");

    return EXIT_SUCCESS;
}
