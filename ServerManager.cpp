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

    while(!mQuit){

        //TODO: main loop
    }
}

ServerManager::ServerManager(const std::vector<std::pair<std::string, int>>& list) {
    
    mQuit = false;

    std::cout << "Local address: " << list[0].first 
              << " port: " << list[0].second << std::endl;
    std::cout << "Send address: " << list[1].first 
              << " port: " << list[1].second << std::endl;
    
    //TODO: init two socket and interface
}

ServerManager::~ServerManager() {

    //TODO: release all sockets and interface
}
