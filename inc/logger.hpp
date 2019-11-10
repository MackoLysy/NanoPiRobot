#pragma once
#include <iostream>
#include <thread>
#include <mutex>



class Logger
{
private:
    Logger(/* args */) {}
    ~Logger() {}
    static std::mutex logmutex;

public:

    template <typename Type> 
    static void log(Type type)
    {
        std::lock_guard<std::mutex> lock(Logger::logmutex);
        std::cout << type << std::endl;
    }
};
