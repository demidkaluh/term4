#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <string>
#include <functional>
#include <iterator>
#include "time_counter.h"
#include "container_cout.h"



template<class Function, class... Args>
void iterate(int n, Function f, Args&&... args)
{
    std::vector<std::thread> threads;

    for (int i = 0; i < n; i++)
    {
        threads.emplace_back(f, args...);
    }

    std::for_each(threads.begin(),threads.end(), std::mem_fn(&std::thread::join));
}


void func(std::string_view sv, int a, int b)
{
    std::cout << sv << " " << a << " " << b << std::endl;
}


int main()
{
    iterate(5, func, "cat", 8, 11);
    iterate(3, []{std::cout << "123" << std::endl;});

    return 0;
}