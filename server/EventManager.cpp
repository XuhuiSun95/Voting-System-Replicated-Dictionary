#include "EventManager.hpp"

EventManager* EventManager::sInstance = nullptr;

EventManager* EventManager::Instance(const int& id, const int& size) {

    if(sInstance==nullptr)
        sInstance = new EventManager(id, size);
    
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

EventManager::EventManager(const int& id, const int& size) {

    mDict = Dictionary::Instance();
    mLog = Log::Instance(id, size);
    mTable = TimeTable::Instance(id, size);
}

EventManager::~EventManager() {

    Dictionary::Release();
    mDict = nullptr;

    Log::Release();
    mLog = nullptr;

    TimeTable::Release();
    mTable = nullptr;
}
