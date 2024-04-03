#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>

std::mutex m;
int x = 0;
std::atomic<int> a = 0;

void func_mutex() 
{
    m.lock();
    for (int i = 0; i < 500'000; i++)
    {
        x++;
    }
    m.unlock();
}

void func_atomic() 
{
    for (int i = 0; i < 500'000; i++)
    {
        a++;
    }
}


class myMutex
{
private:
    std::atomic_flag mIsLocked = ATOMIC_FLAG_INIT;

public:
    void lock()
    {
        while (mIsLocked.test_and_set());
    }

    void unlock()
    {
        mIsLocked.clear();
    }

};

myMutex mm;
int y = 0;
void func_myMutex()
{
    mm.lock();
    for (int i = 0; i < 500'000; i++)
    {
        y++;
    }
    mm.unlock();
}


int main()
{    
    std::thread t1(func_mutex);
    std::thread t2(func_mutex);
    t1.join();
    t2.join();

    std::cout << "Mutex:" << x << std::endl;

    std::thread t3(func_atomic);
    std::thread t4(func_atomic);
    t3.join();
    t4.join();

    std::cout << "Atomic" << a << std::endl;

    std::thread t5(func_myMutex);
    std::thread t6(func_myMutex);
    t5.join();
    t6.join();

    std::cout << "MyMutex" << y << std::endl;

    return 0;
}


