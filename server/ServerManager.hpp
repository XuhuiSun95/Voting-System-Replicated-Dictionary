#ifndef SERVERMANAGER_HPP
#define SERVERMANAGER_HPP

#include <thread>
#include <chrono>
#include "EventManager.hpp"
#include "ServerInput.hpp"
#include "SocketReceive.hpp"
#include "SocketSend.hpp"

class ServerManager {

public:

    static ServerManager* Instance(const int& id, const int& size, const std::vector<std::pair<std::string, int>>& list);
    static void Release();

    void Run();

private:

    static ServerManager* sInstance;

    bool mQuit;
    bool mDebug;
    std::vector<std::pair<std::string, int>> mList;
    
    EventManager* mEvent;
    ServerInput* mInput;
    SocketReceive* mRecv;
    SocketSend* mSend;

    ServerManager(const int& id, const int& size, const std::vector<std::pair<std::string, int>>& list);
    ~ServerManager();

    void InputHandler();
    void RecvHandler();
    void SendHandler();

    void SockConn();
    void SockDisc();
};

#endif
