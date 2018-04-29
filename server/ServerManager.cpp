#include "ServerManager.hpp"

ServerManager* ServerManager::sInstance = nullptr;

ServerManager* ServerManager::Instance(const std::vector<std::pair<std::string, int>>& list) {

    if(sInstance==nullptr)
        sInstance = new ServerManager(list);

    return sInstance;
}

void ServerManager::Release() {

    delete sInstance;
    sInstance = nullptr;
}

void ServerManager::Run() {

    mRecv->Init(mList[0].first, mList[0].second);
    mSend->Init(mList[1].first, mList[1].second);

    //TODO: main loop
    if(!mRecv->Valid()||!mSend->Valid())
        return;

    std::thread recv(&ServerManager::RecvHandler, this);
    std::thread send(&ServerManager::SendHandler, this);

    recv.join();
    send.join();
}

void ServerManager::RecvHandler() {

    std::string msg;

    while(true) {

        msg = mRecv->GetMessage();
        if(msg.compare("-1")==0)
            std::cout << "Accept new connection" << std::endl;
        else
            std::cout << "Receive message: " << msg << std::endl;
    }
}

void ServerManager::SendHandler() {

    while(true) {

        std::this_thread::sleep_for(std::chrono::seconds(3));
        mSend->SendMessage("hello");
    }
}

ServerManager::ServerManager(const std::vector<std::pair<std::string, int>>& list) {
    
    mQuit = false;
    mList = list;
    
    //TODO: init two socket and interface
    mRecv = SocketReceive::Instance(); 
    mSend = SocketSend::Instance();
}

ServerManager::~ServerManager() {

    //TODO: release all sockets and interface
    SocketReceive::Release();
    mRecv = nullptr;

    SocketSend::Release();
    mSend = nullptr;
}
