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

   (*mTable)[row][column] += num;
}

std::string TimeTable::Message() {

    std::string msg = "TT ";

    for(int i=0; i<mSize; i++) {
        for(int j=0; j<mSize; j++)

            msg += std::to_string((*mTable)[i][j]) + " ";
    }

    msg += "EOT";

    return msg;
}

void TimeTable::Print() {

    for(int i=0; i<mSize; i++) {
        for(int j=0; j<mSize; j++)
            std::cout << (*mTable)[i][j] << " ";
        std::cout << std::endl;
    }
}

bool TimeTable::Check(const std::vector<int>& table) {

    bool update = false;

    for(int i=0; i<mSize; i++) {
        for(int j=0; j<mSize; j++) {
            if((*mTable)[i][j]<table[i*mSize+j]) {
                update = true;
                (*mTable)[i][j] = table[i*mSize+j];
            }
        }
    }

    return update;
}

std::pair<int,int> TimeTable::FastForward(const int& target, const int& column, const int& row) {

    std::pair<int,int> forward;

    forward.first = (*mTable)[row][column];
    if(forward.first<target)
        (*mTable)[row][column] = target;
    forward.second = (*mTable)[row][column];

    return forward;
}

int TimeTable::GarbageCollect(const int& id) {

    int seq = INT_MAX;

    for(int i=0; i<mSize; i++)
        seq = std::min(seq, (*mTable)[i][id]);

    return seq;
}

TimeTable::TimeTable(const int& size) {

    mSize = size;
    mTable = new std::vector<std::vector<int>>(size, std::vector<int>(size, 0));
}

TimeTable::~TimeTable() {
    
    delete mTable;
    mTable = nullptr;
}
