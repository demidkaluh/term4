#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <fstream>
#include <algorithm>
#include "../time_counter.h"

using std::cout, std::cin, std::endl;
std::mutex m;
std::string s;


void rw(std::ifstream in)
{
    m.lock();

    std::string line;
    getline(in, line);
    
    std::string noInsertLine = line;
    for(char c : line) if (c != ' ') noInsertLine += c;
    s +=  noInsertLine;

    m.unlock();
}


void check()
{
    m.lock();



    m.unlock();
}

int main()
{
    std::string line;
    std::ifstream in("invisible_man.txt");

    if (in.is_open())
    {
        while (in.peek() != in.eof())
        {
            std::cout << line << std::endl;

            std::thread rwThread(rw, in);
            std::thread checkThread(check);

            rwThread.join();
            checkThread.join();
        }
    }
    in.close();


    return 0;
}