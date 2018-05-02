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

    mDict->Update(s);
    mLog->Update(mSeq++, s, mId);
    mTable->Update(1, mId, mId);
}

void EventManager::PrintDict() {

    mDict->Print();
}

void EventManager::PrintLog() {

    mLog->Print();
}

void EventManager::PrintTable() {

    std::cout << "Server [" << mId << "] :" << std::endl;
    mTable->Print();
}

EventManager::EventManager(const int& id, const int& size) {

    mId = id;
    mSeq = 0;

    mDict = Dictionary::Instance();
    mLog = Log::Instance(size);
    mTable = TimeTable::Instance(size);
}

EventManager::~EventManager() {

    Dictionary::Release();
    mDict = nullptr;

    Log::Release();
    mLog = nullptr;

    TimeTable::Release();
    mTable = nullptr;
}
