#include <iostream>
#include <chrono>
#include <cstdint>
#include <typeinfo>
#include <string>

#if defined(__GNUC__) || defined(__MINGW32__) || defined(__MINGW__)
   #define dFUNCTION __PRETTY_FUNCTION__
#else
   #ifdef _MSC_VER
       #define dFUNCTION __FUNCSIG__
   #else
       #define dFUNCTION __FUNCTION__
   #endif
#endif
 
#define dVIEW_FUNCTION std::cout << dFUNCTION << std::endl 
 
 
#if defined(__GNUC__) || defined(__MINGW32__) || defined(__MINGW__)
 
   #include <cxxabi.h>
   #include <memory>
   
   std::string demangle(const char* name) {
   
       int status = -1; 
       std::unique_ptr<char, void(*)(void*)> res {
           abi::__cxa_demangle(name, NULL, NULL, &status),
           std::free
       };
       return (status == 0) ? res.get() : name ;
   }
#else
 
   std::string demangle(const char* name) 
       { return name; }
 
#endif
 
template <class T> std::string type(const T& t) 
   { return demangle(typeid(t).name()); }
 
 
template <class T> std::string type() 
   { return demangle(typeid(T).name()); }
  
 
#define dECHO(func, ...) \
   std::cout << "Name: " #func ", arg: " #__VA_ARGS__  ",  return: " << type<decltype( func(__VA_ARGS__) )>() << std::endl; 
       
//-------------------------------------------------------------------------------------------------------------------------
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


template <class Function, class... Args>
uint64_t runAndReturnTime(Function f, Args&&... args)
{	
    auto start = std::chrono::high_resolution_clock::now();

    f(args...);

    auto end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}


template <class Function, class... Args>
void PrintInfo(Function f, Args&&... args)
{	
    auto start = std::chrono::high_resolution_clock::now();

    auto result = f(args...);

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "--------------------------------" << std::endl;
    //dECHO(f, args...);
    std::cout << "Result: " << result << std::endl; 
    std::cout << "Time to calculate :" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds" << std::endl;
    std::cout << "--------------------------------" << std::endl;
}


template <class Function, class... Args>
void PrintInfo_void(Function f, Args&&... args)
{	
    auto start = std::chrono::high_resolution_clock::now();

    f(args...);

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "--------------------------------" << std::endl;
    //dECHO(f, args...);
    std::cout << "Time to calculate :" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds" << std::endl;
    std::cout << "--------------------------------" << std::endl;
}



template <class Function, class... Args>
void PrintInfoItReturned(Function f, Args&&... args)
{	
    auto start = std::chrono::high_resolution_clock::now();

    auto result = *f(args...);

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "--------------------------------" << std::endl;
    //dECHO(f, args...);
    std::cout << "Result: " << result << std::endl; 
    std::cout << "Time to calculate :" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds" << std::endl;
    std::cout << "--------------------------------" << std::endl;
}

