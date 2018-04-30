#ifndef SERVERMANAGER_HPP
#define SERVERMANAGER_HPP

#include <vector>
#include <utility>
#include <thread>
#include <mutex>
#include <chrono>
#include "SocketReceive.hpp"
#include "SocketSend.hpp"
#include "ServerInput.hpp"

class ServerManager {

public:

    static ServerManager* Instance(const int& id, const std::vector<std::pair<std::string, int>>& list);
    static void Release();

    void Run();
    void InputHandler();
    void RecvHandler();
    void SendHandler();

    void PrintDict();
    void PrintLog();
    void PrintTable();

private:

    static ServerManager* sInstance;

    bool mQuit;
    int mId;
    std::vector<std::pair<std::string, int>> mList;
    std::vector<int> mDict;
    std::vector<std::vector<int>> mTable;

    std::mutex DictMtx;
    std::mutex TableMtx;
    
    SocketReceive* mRecv;
    SocketSend* mSend;
    ServerInput* mInput;

    ServerManager(const int& id, const std::vector<std::pair<std::string, int>>& list);
    ~ServerManager();
};

#endif
