#ifndef LOG_HPP
#define LOG_HPP

#include <iostream>
#include <string>
#include <vector>

class Log {

public:

    static Log* Instance(const int& size);
    static void Release();

    void Load(const int& id, const std::string& s);
    void Update(const int& seq, const std::string& s, const int& id);
    std::string Message();
    void Print();
    void Clean(const int& id, const int& seq);
    std::string Record();

private:

    static Log* sInstance;

    int mSize;
    std::vector<std::vector<std::string>>* mLog;

    Log(const int& size);
    ~Log();
};

#endif
