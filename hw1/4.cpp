/*
    Задача:

        В данном примере написана функция шаблонная getMax, которая находит максимум из чисел в некотором контейнере.
        При этом вычисления проходят однопоточно.


        Вам нужно написать шаблонную функцию     
            
            template <typename RandIt>
            RandIt getMax(int n, RandIt start, RandIt finish)

        которая будет делать то же самое, но только использовать для этого n потоков.
        Функция должна принимать на вход количество потоков и два итератора, задающих
        диапазон на котором нужно искать максимум.
        Известно, что оба итератора являются random access итераторами.



        Проверить, что эта функция будет работать и для других контейнеров и типов хранящихся в них данных.
        Например, для:

            std::deque<double> d {1.2, 5.1, 8.2, 1.0, 0.2, 5.0, 7.8};
*/








#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <list>
#include <random>
#include <algorithm>
#include <cstdint>
#include <deque>
#include "time_counter.h"
using std::cout, std::endl, std::size_t;
using namespace std::chrono_literals;
std::vector<uint64_t> maxOnSlices = {};


template <typename RandIt>
RandIt getMax(RandIt start, RandIt finish)
{
    RandIt maxIt = start;
    for (auto it = start; it != finish; ++it)
    {
        if (*it > *maxIt)
            maxIt = it;
    }
    return maxIt;
}


template <typename RandIt>
void getMaxAndPushToMaxOnSlices(RandIt start, RandIt finish)
{
    maxOnSlices.push_back(*getMax(start, finish));
}


template <typename RandIt>
RandIt getMaxUsingThreads(RandIt start, RandIt finish, int n)
{
    int elemsInThread = (finish - start) / n;

    std::vector<std::thread> threads;

    for (int i = 0; i < n - 1; i++)
    {
        threads.emplace_back(getMaxAndPushToMaxOnSlices<RandIt>, start + i * elemsInThread, start + i * elemsInThread + elemsInThread - 1);
    }

    threads.emplace_back(getMaxAndPushToMaxOnSlices<RandIt>, start + (n - 1) * elemsInThread, finish);

    std::for_each(threads.begin(),threads.end(), std::mem_fn(&std::thread::join));

    return getMax(maxOnSlices.begin(), maxOnSlices.end());
}


void generatingNumbers(std::vector<uint64_t>& numbers)
{
    cout << "Generating numbers!" << endl;
    numbers[0] = 123456789;
    for (size_t i = 1; i < numbers.size(); ++i)
    {
        numbers[i] = numbers[i - 1] * i + 1;
    }
    cout << "Numbers generated!" << endl;
}


int main()
{
    std::vector<uint64_t> numbers(5e8);
    generatingNumbers(numbers);
    
    
    //std::vector<uint64_t> numbers = {6,2,234,1,11,75,43,23,75,88,987,34,21,34};
    uint64_t t = 0;
    cout << "Enter threads amount: " << endl;
    int n;
    std::cin >> n;
    
    using VecIt = std::vector<uint64_t>::iterator;
    cout << "1 thread:" << endl;
    PrintInfoItReturned(getMax<VecIt>, numbers.begin(), numbers.end());

    cout << n << " threads:" << endl;
    PrintInfoItReturned(getMaxUsingThreads<VecIt>, numbers.begin(), numbers.end(), n);
}

