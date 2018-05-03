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

    mtx.lock();
    mDict->Update(s);
    mLog->Update(mSeq++, s, mId);
    mTable->Update(1, mId, mId);
    mtx.unlock();
}

std::string EventManager::Message() {

    std::string msg;
    mtx.lock();
    msg += mTable->Message();
    msg += " ";
    msg += mLog->Message();
    mtx.unlock();

    return msg;
}

void EventManager::Update(const std::string& s) {

    size_t sot = s.find("TT ");
    size_t eot = s.find("EOT");
    std::string tt = s.substr(sot+3, eot-sot-3);

    std::vector<int> ttr;
    size_t offset = 0;
    while(tt.find(" ", offset)!=std::string::npos) {

        size_t len = tt.find(" ", offset) - offset;
        ttr.push_back(std::stoi(tt.substr(offset, len)));
        offset += len+1;
    }

    mtx.lock();
    if(mTable->Check(ttr)) {

        int size = sqrt(ttr.size());
        int recv = (mId+size-1)%size;

        for(int i=0; i<size; i++) {

            std::pair<int,int> ff = mTable->FastForward(ttr[recv*size+i], i, mId);
            if(ff.first<ff.second) {

                for(int j=ff.first; j<ff.second; j++) {

                    std::string target = std::to_string(i) + " " + std::to_string(j) + " Vote";
                    size_t begin = s.find(target) + std::to_string(i).length() + 1;
                    size_t end = s.find("|", begin);
                    target = s.substr(begin, end-begin);

                    size_t ws = target.find(" ");
                    int seq = std::stoi(target.substr(0, ws));
                    target = target.substr(ws+1);

                    mLog->Update(seq, target, i);
                    mDict->Update(target);
                }
            }

            //int collect = mTable->GrabageCollect(i);

        }
    }
    mtx.unlock();
}

void EventManager::PrintDict() {

    mtx.lock();
    mDict->Print();
    mtx.unlock();
}

void EventManager::PrintLog() {

    mtx.lock();
    mLog->Print();
    mtx.unlock();
}

void EventManager::PrintTable() {

    std::cout << "Server [" << mId << "] :" << std::endl;
    mtx.lock();
    mTable->Print();
    mtx.unlock();
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
