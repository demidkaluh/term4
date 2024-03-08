#include <iostream>
#include <chrono>
#include <cstdint>

template <class Function, class... Args>
auto runAndCount(uint64_t& time, Function f, Args&&... args)
{	
    auto start = std::chrono::high_resolution_clock::now();

    auto result = f(args...);

    auto end = std::chrono::high_resolution_clock::now();

    time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    return result;
}


template <class Function, class... Args>
void runAndCount_void(uint64_t& time, Function f, Args&&... args)
{	
    auto start = std::chrono::high_resolution_clock::now();

    f(args...);

    auto end = std::chrono::high_resolution_clock::now();

    time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

/*
template <class Function, class... Args>
uint64_t runAndReturnTime(Function f, Args&&... args)
{	
    auto start = std::chrono::high_resolution_clock::now();

    f(args...);

    auto end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}


template <class Function, class... Args>
void runAndPrintTime(Function f, Args&&... args)
{	
    auto start = std::chrono::high_resolution_clock::now();

    f(args...);

    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "Time to calculate :" std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds" << std::endl;
}


//Для функций с итераторами

template <class Function, class RandIt, class... Args>
auto runAndCount(uint64_t& time, Function f, RandIt startIt, RandIt finishIt, Args&&... args)
{	
    auto start = std::chrono::high_resolution_clock::now();

    auto result = f(startIt, finishIt, args...);

    auto end = std::chrono::high_resolution_clock::now();

    time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    return result;
}


template <class Function, class RandIt, class... Args>
void runAndCount_void(uint64_t& time, Function f, RandIt startIt, RandIt finishIt, Args&&... args)
{	
    auto start = std::chrono::high_resolution_clock::now();

    f(startIt, finishIt, args...);

    auto end = std::chrono::high_resolution_clock::now();

    time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}*/




