#include <fstream>
#include <sstream>
#include "ServerManager.hpp"

int main(int argc, char* argv[]) {

    if(argc!=2) {

        std::cerr << "Usage: " << argv[0] << " <config file>" << std::endl;
        return 1;
    }

    std::ifstream ifs(argv[1]);
    std::vector<std::pair<std::string, int>> list;

    std::string s;
    std::string ipaddr;
    int port;
    int count = 0;

    while(!ifs.eof()) {
        std::getline(ifs, s);
        std::istringstream iss(s);
        iss >> ipaddr;
        std::cout << ipaddr << std::endl;
        iss >> port;
        std::cout << port << std::endl;
        list.push_back(std::make_pair(ipaddr, port));
        count++;
    }
    std::cout << count << std::endl;
    //for(int i=0; i<2; i++) {

    //    std::getline(ifs, s);
    //    std::istringstream iss(s);
    //    iss >> ipaddr;
    //    std::cout << ipaddr << std::endl;
    //    iss >> port;
    //    std::cout << port << std::endl;
    //    list.push_back(std::make_pair(ipaddr, port));
    //}

    //if(!ifs.eof()){

    //    std::cerr << "Invalid configuration file! Conf format:" << std::endl;
    //    std::cerr << "<local address> <local port>" << std::endl;
    //    std::cerr << "<send address> <send port>" << std::endl;

    //    std::getline(ifs, ipaddr);
    //    std::cout << ipaddr << std::endl;

    //    ifs.close();
    //    return 1;
    //}

    ifs.close();

    ServerManager* server = ServerManager::Instance(list);

    server->Run();

    ServerManager::Release();
    server = nullptr;

    return 0;
}
