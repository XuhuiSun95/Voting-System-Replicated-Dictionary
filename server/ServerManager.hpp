#ifndef SERVERMANAGER_HPP
#define SERVERMANAGER_HPP

#include <vector>
#include <utility>
#include <thread>
#include <chrono>
#include "SocketReceive.hpp"
#include "SocketSend.hpp"

class ServerManager {

public:

    static ServerManager* Instance(const std::vector<std::pair<std::string, int>>& list);
    static void Release();

    void Run();
    void RecvHandler();
    void SendHandler();

private:
    
    static ServerManager* sInstance;

    bool mQuit;
    std::vector<std::pair<std::string, int>> mList;

    //TODO socket and interface
    SocketReceive* mRecv;
    SocketSend* mSend;

    ServerManager(const std::vector<std::pair<std::string, int>>& list);
    ~ServerManager();
};

#endif
