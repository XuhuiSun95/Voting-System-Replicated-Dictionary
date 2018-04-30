#include "ServerManager.hpp"

ServerManager* ServerManager::sInstance = nullptr;

ServerManager* ServerManager::Instance(const int& id, const std::vector<std::pair<std::string, int>>& list) {

    if(sInstance==nullptr)
        sInstance = new ServerManager(id, list);

    return sInstance;
}

void ServerManager::Release() {

    delete sInstance;
    sInstance = nullptr;
}

void ServerManager::Run() {

    mRecv->Init(mList[0].first, mList[0].second);

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
            case 0: // start
                mSend = SocketSend::Instance();
                if(!mSend->Valid())
                    mSend->Init(mList[1].first, mList[1].second);
                break;
            case 1: // stop
                if(mSend!=nullptr) {
                    SocketSend::Release();
                    mSend = nullptr;
                }
                break;
            case 2: // Vote, A
                break;
            case 3: // Vote, B
                break;
            case 4: // printDict.
                PrintDict();
                break;
            case 5: // printLog
                PrintLog();
                break;
            case 6: // printTable
                PrintTable();
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

void ServerManager::PrintDict() {

    DictMtx.lock();
    std::cout << "{A:" << mDict[0] << ",B:" << mDict[1] << "}" << std::endl;
    DictMtx.unlock();
}

void ServerManager::PrintLog() {
}

void ServerManager::PrintTable() {

    TableMtx.lock();
    for(auto it=mTable.begin(); it!=mTable.end(); ++it) {
        for(auto it2=it->begin(); it2!=it->end(); ++it2)
            std::cout << *it2 << " ";
        std::cout << std::endl;
    }
    TableMtx.unlock();
}

ServerManager::ServerManager(const int& id, const std::vector<std::pair<std::string, int>>& list) {
    
    mQuit = false;
    mId = id;
    mList = list;
    mDict = {0,0};
    mTable = {{0,0,0},{0,0,0},{0,0,0}};

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
