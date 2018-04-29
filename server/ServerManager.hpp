#ifndef SERVERMANAGER_HPP
#define SERVERMANAGER_HPP

#include <vector>
#include <utility>
#include <thread>
#include <chrono>
#include "SocketReceive.hpp"
#include "SocketSend.hpp"
#include "ServerInput.hpp"

class ServerManager {

public:

    static ServerManager* Instance(const std::vector<std::pair<std::string, int>>& list);
    static void Release();

    void Run();
    void InputHandler();
    void RecvHandler();
    void SendHandler();

private:

    static ServerManager* sInstance;

    bool mQuit;
    std::vector<std::pair<std::string, int>> mList;
    
    SocketReceive* mRecv;
    SocketSend* mSend;
    ServerInput* mInput;

    ServerManager(const std::vector<std::pair<std::string, int>>& list);
    ~ServerManager();
};

#endif
