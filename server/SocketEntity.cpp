#include "SocketEntity.hpp"

SocketEntity::SocketEntity() {

    mValid = false;
}

SocketEntity::~SocketEntity() {

    close(mSockfd);
}

void SocketEntity::Init(const std::string& ipaddr, const int& port) {

    if((mSockfd = socket(AF_INET, SOCK_STREAM, 0))<0) {
        std::cout << "Socket creation error" << std::endl;
        return;
    }

    memset(&mAddress, '0', sizeof(mAddress));
    mAddress.sin_family = AF_INET;
    mAddress.sin_port = htons(port);

    mValid = true;
}

bool SocketEntity::Valid() {

    return mValid;
}

int SocketEntity::Sockfd() {

    return mSockfd;
}

struct sockaddr_in* SocketEntity::AddressRef() {

    return &mAddress;
}

struct sockaddr_in SocketEntity::Address() {

    return mAddress;
}

struct in_addr* SocketEntity::InRef() {

    return &mAddress.sin_addr;
}

void SocketEntity::Address(uint32_t type) {

    mAddress.sin_addr.s_addr = type;
}
