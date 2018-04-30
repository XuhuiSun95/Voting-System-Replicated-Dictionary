#include "EventManager.hpp"

EventManager* EventManager::sInstance = nullptr;

EventManager* EventManager::Instance() {

    if(sInstance==nullptr)
        sInstance = new EventManager();
    
    return sInstance;
}

void EventManager::Release() {

    delete sInstance;
    sInstance = nullptr;
}

void EventManager::Vote(const std::string& s) {
}

void EventManager::PrintDict() {

    mDict->Print();
}

void EventManager::PrintLog() {

    mLog->Print();
}

void EventManager::PrintTable() {

    mTable->Print();
}

EventManager::EventManager() {

    mDict = Dictionary::Instance();
    mLog = Log::Instance(3);
    mTable = TimeTable::Instance(3);
}

EventManager::~EventManager() {

    Dictionary::Release();
    mDict = nullptr;

    Log::Release();
    mLog = nullptr;

    TimeTable::Release();
    mTable = nullptr;
}
