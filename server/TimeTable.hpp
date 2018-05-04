#ifndef TIMETABLE_HPP
#define TIMETABLE_HPP

#include <climits>
#include <iostream>
#include <string>
#include <vector>
#include <utility>

class TimeTable {

public:

    static TimeTable* Instance(const int& size);
    static void Release();

    void Load(const std::vector<int>& table);
    void Update(const int& num, const int& column, const int& row);
    std::string Message();
    void Print();
    bool Check(const std::vector<int>& table);
    std::pair<int,int> FastForward(const int& target, const int& column, const int& row);
    int GarbageCollect(const int& id);
    std::string Record();

private:

    static TimeTable* sInstance;

    int mSize;
    std::vector<std::vector<int>>* mTable;

    TimeTable(const int& size);
    ~TimeTable();
};

#endif
