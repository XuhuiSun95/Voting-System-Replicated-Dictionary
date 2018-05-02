#ifndef LOG_HPP
#define LOG_HPP

#include <iostream>
#include <string>
#include <vector>
#include <mutex>

class Log {

public:

    static Log* Instance(const int& size);
    static void Release();

    void Update(const int& seq, const std::string& s, const int& id);
    void Print();

private:

    static Log* sInstance;

    std::mutex mtx;
    int mSize;
    std::vector<std::vector<std::string>>* mLog;

    Log(const int& size);
    ~Log();
};

#endif
