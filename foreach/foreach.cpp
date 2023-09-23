#include <iostream>
#include <vector>
#include <future>

template <typename I, typename F>
void parallel_for_each(I first, I last, const F& func)
{
    auto size = std::distance(first, last);
    if (size <= 1)
    {
        func(*first);
        return;
    }
    auto future = std::async(parallel_for_each<I, F>, first, std::next(first, size / 2), func);
    parallel_for_each<I, F>(std::next(first, size / 2), last, func);
}

template <typename T>
void display(T& container)
{
    for (auto el : container) {
        std::cout << el << " ";
    }
    std::cout << std::endl;
}

int main()
{
    std::vector<int> vec { 24, 66, 20, 79, 30, 16, 19, 62, 94, 59, 0, 7, 59, 90, 84, 60, 95, 62 };
    auto increase = [](int& num)
    {
        num++;
    };
    std::cout << "Before func: " << std::endl;
    display(vec);
    parallel_for_each(vec.begin(), vec.end(), increase);
    std::cout << "After func: " << std::endl;
    display(vec);
}

