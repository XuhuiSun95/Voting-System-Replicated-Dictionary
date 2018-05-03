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

void Log::Update(const int& seq, const std::string& s, const int& id) {

    std::string log = std::to_string(seq) + " " + s;

    (*mLog)[id].push_back(log);
}

std::string Log::Message() {

    std::string msg = "LOG";

    for(int i=0; i<mSize; i++) {
        for(int j=0; j<(*mLog)[i].size(); j++)

            msg += "|" + std::to_string(i) + " " + (*mLog)[i][j];
    }

    msg += "|EOL";

    return msg;
}

void Log::Print() {

    std::cout << "{";
    bool flag = true;

    for(int i=0; i<mSize; i++) {
        for(int j=0; j<(*mLog)[i].size(); j++) {

            std::size_t vote = (*mLog)[i][j].find("Vote");
            if(vote!=std::string::npos) {
                if(flag) {
                    std::cout << "{";
                    flag = false;
                }
                else {
                    std::cout << ",{";
                }
                std::cout << (*mLog)[i][j].substr(vote) << "}";
            }
        }
    }

    std::cout << "}" << std::endl;
}

void Log::Clean(const int& id, const int& seq) {

    for(int i=(*mLog)[id].size()-1; i>=0; i--) {

        size_t ws = (*mLog)[id][i].find(" ");
        int curr = std::stoi((*mLog)[id][i].substr(0, ws));
        if(curr<seq)
            (*mLog)[id].erase((*mLog)[id].begin()+i);
    }
}

Log::Log(const int& size) {

    mSize = size;
    mLog = new std::vector<std::vector<std::string>>(size, std::vector<std::string>());
}

Log::~Log() {

    delete mLog;
    mLog = nullptr;
}
