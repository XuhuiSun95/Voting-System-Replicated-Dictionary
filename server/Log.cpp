#include "Log.hpp"

Log* Log::sInstance = nullptr;

Log* Log::Instance(const int& size) {

    if(sInstance==nullptr)
        sInstance = new Log(size);

    return sInstance;
}

void Log::Release() {

    delete sInstance;
    sInstance = nullptr;
}

void Log::Print() {

    std::cout << "{";
    mtx.lock();

    for(int i=0; i<mSize; i++) {
        for(int j=0; j<(*mLog)[i].size(); j++) {

            std::size_t vote = (*mLog)[i][j].find("Vote");
            if(vote!=std::string::npos) {
                std::cout << "{" << (*mLog)[i][j].substr(vote) << "}";
                if(i!=mSize-1&&j!=(*mLog)[mSize-1].size()-1)
                    std::cout << ",";
            }
        }
    }

    mtx.unlock();
    std::cout << "}" << std::endl;
}

Log::Log(const int& size) {

    mSize = size;
    mLog = new std::vector<std::vector<std::string>>(size, std::vector<std::string>());
}

Log::~Log() {

    delete mLog;
    mLog = nullptr;
}
