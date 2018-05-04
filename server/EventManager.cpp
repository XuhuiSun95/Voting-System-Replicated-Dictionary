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
    msg += "Send from site [" + std::to_string(mId) + "] ";
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

            int collect = mTable->GarbageCollect(i);
            mLog->Clean(i, collect);
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

void EventManager::Record() {

    std::string filename = "record/state_" + std::to_string(mId);
    std::ofstream ofs;
    ofs.open(filename, std::ios::out | std::ios::trunc);

    ofs << mSeq << "\n";
    ofs << mDict->Record();
    ofs << mLog->Record();
    ofs << mTable->Record();

    ofs.close();
}

EventManager::EventManager(const int& id, const int& size) {

    mId = id;
    mSeq = 0;

    mDict = Dictionary::Instance();
    mLog = Log::Instance(size);
    mTable = TimeTable::Instance(size);

    std::string filename = "record/state_" + std::to_string(mId);
    std::ifstream ifs;
    ifs.open(filename, std::ios::in);

    if(ifs.good()) {
        std::cout << "Load from previous state!" << std::endl;
        std::string line;
        std::getline(ifs, line);
        mSeq = std::stoi(line);
        std::getline(ifs, line);
        size_t ws = line.find(" ");
        mDict->Load(std::stoi(line.substr(0,ws)), std::stoi(line.substr(ws+1)));
        for(int i=0; i<size; i++) {
            std::getline(ifs, line);
            int count = std::stoi(line);
            for(int j=0; j<count; j++) {
                std::getline(ifs, line);
                mLog->Load(i, line);
            }
        }
        std::getline(ifs, line);
        int offset = 0;
        std::vector<int> tt;
        for(int i=0; i<size*size; i++) {
            ws = line.find(" ", offset);
            tt.push_back(std::stoi(line.substr(offset, ws-offset)));
            offset = ws + 1;
        }
        mTable->Load(tt);
    }
}

EventManager::~EventManager() {

    Dictionary::Release();
    mDict = nullptr;

    Log::Release();
    mLog = nullptr;

    TimeTable::Release();
    mTable = nullptr;
}
