#include <iostream>
#include <vector>
#include <thread>
#include <iterator>
#include <algorithm>
#include <cstdint>
#include <functional>
#include "container_cout.h"
#include "time_counter.h"

using std::cout, std::vector, std::endl;

class IsLess
{
public:
    bool operator()(const uint64_t& x, const uint64_t& y) const
    {
        return x > y;
    }
};
IsLess comp1;

template<class RandIt, class Comparator>
void parallelSort(int n, RandIt start, RandIt finish, Comparator comp)
{
    std::vector<std::thread> threads;
    int elemsInThread = (finish - start) / n;

    for (int i = 0; i < n - 1; i++)
    {
        threads.emplace_back(std::sort<RandIt, Comparator>, start + i * elemsInThread, start + i * elemsInThread + elemsInThread - 1, comp);
    }
    threads.emplace_back(std::sort<RandIt, Comparator>, start + (n - 1) * elemsInThread, finish, comp);

    std::vector<RandIt> vit0;

    for (int i = 0; i < n; i++)
    {
        vit0.push_back(start + i * elemsInThread);
    }
    std::vector<RandIt> vit;
    for (int i = 0; i < n; i++)
    {
        vit[i] = vit0[i];
    }
    std::vector<
    while(!vit.empty())
    {

    }

    std::for_each(threads.begin(),threads.end(), std::mem_fn(&std::thread::join));
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
    //std::vector<uint64_t> numbers(5e8);
    //generatingNumbers(numbers);
    std::vector<uint64_t> v = {6,7,3,2,66,3,534,11,98,76,5,43,22,777,54,23,76,54,32,77,87};
    std::vector<uint64_t> vn = {6,7,3,2,66,3,534,11,98,76,5,43,22,777,54,23,76,54,32,77,87};
    
    using VecIt = std::vector<uint64_t>::iterator;
    uint64_t t = 0;
    int n = 0;
    std::cout << "Enter thread amount:";
    std::cin >> n;
    std::cout << "1 thread" << std::endl;
    PrintInfo_void(std::sort<VecIt, IsLess>, v.begin(), v.end(), comp1);
    std::cout << v << std::endl;
    std::cout << n << " threads" << std::endl;
    PrintInfo_void(parallelSort<VecIt, IsLess>, n, vn.begin(), vn.end(), comp1);
    std::cout << vn << std::endl;

    return 0;

}