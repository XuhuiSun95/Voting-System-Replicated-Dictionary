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

    //TODO: main loop
    std::thread input(&ServerManager::InputHandler, this);
    std::thread recv(&ServerManager::RecvHandler, this);
    std::thread send(&ServerManager::SendHandler, this);

    input.join();
    recv.join();
    send.join();
}

void ServerManager::InputHandler() {

    int opt;

    while(true) {

        opt = mInput->RequestHandler();
        switch(opt) {
            case 0:
                mSend = SocketSend::Instance();
                if(!mSend->Valid())
                    mSend->Init(mList[1].first, mList[1].second);
                break;
            case 1:
                if(mSend!=nullptr) {
                    SocketSend::Release();
                    mSend = nullptr;
                }
                break;
            default:
                std::cout << "Unknow command" << std::endl;
        }
    }
}

void ServerManager::RecvHandler() {

    std::string msg;

    while(true) {

        if(mRecv->Valid()){

            msg = mRecv->GetMessage();

            if(msg.compare("-1")==0)
                std::cout << "Accept new connection" << std::endl;
            else
                std::cout << "Receive message: " << msg << std::endl;
        }
    }
}

void ServerManager::SendHandler() {

    while(true) {

        std::this_thread::sleep_for(std::chrono::seconds(3));
        if(mSend!=nullptr && mSend->Valid()) {
            mSend->SendMessage("hello");
            std::cout << "message sent!" << std::endl;
        }
    }
}

ServerManager::ServerManager(const std::vector<std::pair<std::string, int>>& list) {
    
    mQuit = false;
    mList = list;
    
    mInput = ServerInput::Instance();
    mRecv = SocketReceive::Instance(); 
    mSend = SocketSend::Instance();
}

ServerManager::~ServerManager() {

    SocketSend::Release();
    mSend = nullptr;

    SocketReceive::Release();
    mRecv = nullptr;

    ServerInput::Release();
    mInput = nullptr;
}
