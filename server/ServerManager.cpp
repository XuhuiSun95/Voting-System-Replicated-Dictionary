#include "ServerManager.hpp"

ServerManager* ServerManager::sInstance = nullptr;

ServerManager* ServerManager::Instance(const int& id, const int& size, const std::vector<std::pair<std::string, int>>& list) {

    if(sInstance==nullptr)
        sInstance = new ServerManager(id, size, list);

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

    mEvent->Record();
}

ServerManager::ServerManager(const int& id, const int& size, const std::vector<std::pair<std::string, int>>& list) {

    mQuit = false;
    mConn = false;
    mDebug = true;
    mList = list;

    mEvent = EventManager::Instance(id, size);
    mInput = ServerInput::Instance();
    mRecv = SocketReceive::Instance();
}

ServerManager::~ServerManager() {

    SocketReceive::Release();
    mRecv = nullptr;

    ServerInput::Release();
    mInput = nullptr;

    EventManager::Release();
    mEvent = nullptr;
}

void ServerManager::InputHandler() {

    int opt;

    while(!mQuit) {

        opt = mInput->RequestHandler();
        switch(opt) {
            case 0: // start
                mConn = true;
                break;
            case 1: // stop
                mConn = false;
                break;
            case 2: // Vote,A
                mEvent->Vote("Vote,A");
                break;
            case 3: // Vote,B
                mEvent->Vote("Vote,B");
                break;
            case 4: // printDict.
                mEvent->PrintDict();
                break;
            case 5: // printLog
                mEvent->PrintLog();
                break;
            case 6: // printTable
                mEvent->PrintTable();
                break;
            case 7: // Debug
                mDebug = !mDebug;
                break;
            case 8: // shutdown
                mQuit = true;
                break;
            default:
                std::cout << "Unknow command" << std::endl;
                std::cout << "Valid command:" << std::endl;
                std::cout << "start      -- start connection" << std::endl;
                std::cout << "stop       -- close connection" << std::endl;
                std::cout << "Vote,X     -- Vote, X is either A or B" << std::endl;
                std::cout << "printDict. -- print dictionary" << std::endl;
                std::cout << "printLog   -- print log" << std::endl;
                std::cout << "printTable -- print time table" << std::endl;
                std::cout << "debug      -- display debug message(send&recv msg)" << std::endl;
                std::cout << "shutdown   -- shut down server" << std::endl;
        }
        std::cout << std::endl;
    }
}

void ServerManager::RecvHandler() {

    while(!mQuit) {

        if(mRecv->Valid()){

            std::string msg = mRecv->GetMessage();
            if(msg.compare("-1")!=0 && msg.compare("")!=0) {

                if(mDebug)
                    std::cout << "Receive message: " << msg << std::endl;
                mEvent->Update(msg);
            }
        }
    }
}

void ServerManager::SendHandler() {

    while(!mQuit) {

        std::this_thread::sleep_for(std::chrono::seconds(3));
        if(mConn) {

            ServerManager::SockConn();

            if(mSend->Valid()) {
                if(mDebug)
                    std::cout << "message sent!" << std::endl;
                mSend->SendMessage(mEvent->Message());
            }

            ServerManager::SockDisc();
        }
    }
}

void ServerManager::SockConn() {

    mSend = SocketSend::Instance();
    if(!mSend->Valid())
        mSend->Init(mList[1].first, mList[1].second);
}

void ServerManager::SockDisc() {

    if(mSend!=nullptr) {
        SocketSend::Release();
        mSend = nullptr;
    }
}
