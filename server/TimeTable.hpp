#ifndef TIMETABLE_HPP
#define TIMETABLE_HPP

#include <iostream>
#include <vector>
#include <mutex>

class TimeTable {

public:

    static TimeTable* Instance(const int& id, const int& size);
    static void Release();

    void Print();

private:

    static TimeTable* sInstance;

    std::mutex mtx;
    int mId;
    int mSize;
    std::vector<std::vector<int>>* mTable;

    TimeTable(const int& id, const int& size);
    ~TimeTable();
};

#endif
