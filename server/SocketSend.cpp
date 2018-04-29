#include "SocketSend.hpp"

SocketSend* SocketSend::sInstance = nullptr;

SocketSend* SocketSend::Instance() {

    if(sInstance==nullptr)
        sInstance = new SocketSend();

    return sInstance;
}

void SocketSend::Release() {

    delete sInstance;
    sInstance = nullptr;
}

void SocketSend::Init(const std::string& ipaddr, const int& port) {

    SocketEntity::Init(ipaddr, port);

    if(SocketEntity::Valid()) {

        if(inet_pton(AF_INET, ipaddr.c_str(), SocketEntity::InRef())<=0) {
            std::cout << "Invalid pair server address/ Address not supported" << std::endl;
            return;
        }

        if(connect(SocketEntity::Sockfd(), (struct sockaddr *)SocketEntity::AddressRef(), sizeof(SocketEntity::Address()))<0) {
            std::cout << "Connection Failed" << std::endl;
            return;
        }

        mValid = true;
    }
}

bool SocketSend::Valid() {

    return mValid;
}

void SocketSend::SendMessage(const std::string& msg) {

    send(SocketEntity::Sockfd(), msg.c_str(), msg.length(), 0);
}

SocketSend::SocketSend() {
    
    mValid = false;
}

SocketSend::~SocketSend() {
}
