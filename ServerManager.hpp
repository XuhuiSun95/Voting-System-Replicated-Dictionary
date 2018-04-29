#ifndef SERVERMANAGER_HPP
#define SERVERMANAGER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <utility>

class ServerManager {

public:

    static ServerManager* Instance(const std::vector<std::pair<std::string, int>>& list);
    static void Release();

    void Run();

private:
    
    static ServerManager* sInstance;
    bool mQuit;

    ServerManager(const std::vector<std::pair<std::string, int>>& list);
    ~ServerManager();
};

#endif
