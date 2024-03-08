#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <functional>

using namespace std::chrono_literals;
using std::cout, std::cin, std::endl;


void func(int i, int n)
{
    if (i == n) return;

    cout << "Thread " << i << " started" << endl;
    std::this_thread::sleep_for(2s);

    
    std::thread t(func, i + 1, n);
    t.join();

    cout << "Thread " << i << " finished" << endl;

}


int main()
{
    int n = 0;
    cin >> n;

    std::thread t(func, 1, n);
    t.join();

    return 0;
}