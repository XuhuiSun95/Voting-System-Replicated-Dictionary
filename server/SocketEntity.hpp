#ifndef SOCKETENTITY_HPP
#define SOCKETENTITY_HPP

#include <cstring>
#include <iostream>
#include <string>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

class SocketEntity {

public:

    SocketEntity();
    ~SocketEntity();

    void Init(const std::string& ipaddr, const int& port);
    bool Valid();
    int Sockfd();
    struct sockaddr_in* AddressRef();
    struct sockaddr_in Address();
    struct in_addr* InRef();
    void Address(uint32_t type);

private:

    bool mValid;
    int mSockfd;
    struct sockaddr_in mAddress;
};

#endif
