#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP

#include "Dictionary.hpp"
#include "Log.hpp"
#include "TimeTable.hpp"

class EventManager {

public:

    static EventManager* Instance();
    static void Release();

    void Vote(const std::string& s);
    void PrintDict();
    void PrintLog();
    void PrintTable();

private:
    
    static EventManager* sInstance;

    Dictionary* mDict;
    Log* mLog;
    TimeTable* mTable;

    EventManager();
    ~EventManager();
};

#endif
