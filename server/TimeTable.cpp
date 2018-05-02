#include "TimeTable.hpp"

TimeTable* TimeTable::sInstance = nullptr;

TimeTable* TimeTable::Instance(const int& size) {

    if(sInstance==nullptr)
        sInstance = new TimeTable(size);

    return sInstance;
}

void TimeTable::Release() {

    delete sInstance;
    sInstance = nullptr;
}

void TimeTable::Update(const int& num, const int& column, const int& row) {

   mtx.lock();
   (*mTable)[row][column] += num;
   mtx.unlock();
}

void TimeTable::Print() {

    mtx.lock();
    for(int i=0; i<mSize; i++) {
        for(int j=0; j<mSize; j++)
            std::cout << (*mTable)[i][j] << " ";
        std::cout << std::endl;
    }
    mtx.unlock();
}

TimeTable::TimeTable(const int& size) {

    mSize = size;
    mTable = new std::vector<std::vector<int>>(size, std::vector<int>(size, 0));
}

TimeTable::~TimeTable() {
    
    delete mTable;
    mTable = nullptr;
}
