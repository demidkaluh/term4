#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <random>
#include <algorithm>
#include <cstdint>
#include <functional>
#include <iterator>
#include "time_counter.h"
#include "container_cout.h"


using std::cout, std::endl, std::size_t;
using namespace std::chrono_literals;
std::vector<uint64_t> maxOnSlices = {};

uint64_t getMax(const std::vector<uint64_t>& v)
{
    uint64_t result = v.at(0);
    for (auto el : v)
    {
        if (el > result)
            result = el;
    }

    return result;
}

//--------------------------------------------------------------------------------------------------------------------------
void getMaxByIterAndPushToMaxOnSlices(std::vector<uint64_t>::const_iterator start, std::vector<uint64_t>::const_iterator finish)
{
    auto mx = *start;
    for (auto iter = start; iter < finish; iter++)
    {
        if (*iter > mx)
            mx = *iter;
    }

    maxOnSlices.push_back(mx);
}


uint64_t getMaxUsingThreads(int n, const std::vector<uint64_t>& v)
{
    int elemsInThread = v.size() / n;

    std::vector<std::thread> threads;

    for (int i = 0; i < n - 1; i++)
    {
        threads.emplace_back(getMaxByIterAndPushToMaxOnSlices, v.begin() + i * elemsInThread, v.begin() + i * elemsInThread + elemsInThread - 1);
    }

    threads.emplace_back(getMaxByIterAndPushToMaxOnSlices, v.begin() + (n - 1) * elemsInThread, v.end());

    std::for_each(threads.begin(),threads.end(), std::mem_fn(&std::thread::join));

    uint64_t result = getMax(maxOnSlices);

    return result;
}
//--------------------------------------------------------------------------------------------------------------------------

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
    //std::vector<uint64_t> numbers = {1, 13, 25, 3, 2, 11, 5, 7, 43, 12, 4, 23, 66, 9};

    cout << "Enter threads amount: " << endl;
    int n;
    std::cin >> n;

    uint64_t t = 0;
    uint64_t m = runAndCount(t, getMax, numbers);
    cout << "1 thread:" << endl;
    cout << "Maximum = " << m << endl;
    cout << "Time to calclulate max = " << t << " milliseconds." << endl;

    uint64_t mn = runAndCount(t, getMaxUsingThreads, n, numbers);
    cout << n << " threads:" << endl;
    cout << "Maximum = " << mn << endl;
    cout << "Time to calclulate max = " << t << " milliseconds." << endl;
}