#ifndef TIMETABLE_HPP
#define TIMETABLE_HPP

#include <iostream>
#include <vector>
#include <mutex>

class TimeTable {

public:

    static TimeTable* Instance(const int& size);
    static void Release();

    void Update(const int& num, const int& column, const int& row);
    void Print();

private:

    static TimeTable* sInstance;

    std::mutex mtx;
    int mSize;
    std::vector<std::vector<int>>* mTable;

    TimeTable(const int& size);
    ~TimeTable();
};

#endif
