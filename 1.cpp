#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <functional>

using namespace std::chrono_literals;
using std::cout, std::cin, std::endl;


void func(int i)
{
    cout << "Thread " << i << " started" << endl;
    std::this_thread::sleep_for(2 * i * 1s);
    cout << "Thread " << i << " finished" << endl;
}


int main()
{
    int n = 0;
    cin >> n;

    std::vector<std::thread> threads;

    for (int i = 1; i <= n; i++)
    {
        threads.push_back(std::thread(func, i));
    }

    std::for_each(threads.begin(),threads.end(), std::mem_fn(&std::thread::join));

    return 0;
}