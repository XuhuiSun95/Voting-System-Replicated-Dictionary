#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP

#include "Dictionary.hpp"
#include "Log.hpp"
#include "TimeTable.hpp"

class EventManager {

public:

    static EventManager* Instance(const int& id, const int& size);
    static void Release();

    void Vote(const std::string& s);
    void PrintDict();
    void PrintLog();
    void PrintTable();

private:
    
    static EventManager* sInstance;

    int mId;
    int mSeq;

    Dictionary* mDict;
    Log* mLog;
    TimeTable* mTable;

    EventManager(const int& id, const int& size);
    ~EventManager();
};

#endif
