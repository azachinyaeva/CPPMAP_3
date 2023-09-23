#include <iostream>
#include <vector>
#include <future>


void display(const std::vector<int>& vec) 
{
    for (auto i : vec) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

void find_min(int start, std::vector<int>& vec, std::promise<int> prom) 
{
    int min = start;
    for (int j = start; j < vec.size(); ++j) 
    {
        min = (vec.at(j) < vec.at(min)) ? j : min;
    }
    prom.set_value(min);

};

void sort(std::vector<int>& vec) {
    int temp = 0;
    int next_min = 0;
    for (int i = 0; i < vec.size(); ++i) 
    {
        std::promise<int> prom;
        std::future<int> ft = prom.get_future();
        std::future<void> future = std::async(std::launch::async, find_min, i, std::ref(vec), std::move(prom));
        future.wait();
        next_min = ft.get();
        temp = vec.at(next_min);
        vec.at(next_min) = vec.at(i);
        vec.at(i) = temp;
    }
}

int main()
{
    std::vector<int> vec = { 24, 66, 20, 79, 30, 16, 19, 62, 94, 59, 0, 7, 59, 90, 84, 60, 95, 62 };
    std::cout << "Before sort: " << std::endl;
    display(vec);
    sort(vec);
    display(vec);
}

