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

    while(std::getline(ifs, s)) {
        
        count++;
        if(count>2) {
            std::cerr << "Invalid configuration file!" << std::endl;
            std::cerr << "Conf format:" << std::endl;
            std::cerr << "<local address> <local port>" << std::endl;
            std::cerr << "<send address> <send port>" << std::endl;

            ifs.close();
            return 1;
        }

        std::istringstream iss(s);
        iss >> ipaddr;
        iss >> port;
        list.push_back(std::make_pair(ipaddr, port));
    }

    ifs.close();

    if(count!=2) {
        std::cerr << "Unmatched input!" << std::endl; 
        std::cerr << "Conf format:" << std::endl;
        std::cerr << "<local address> <local port>" << std::endl;
        std::cerr << "<send address> <send port>" << std::endl;

        return 1;
    }

    ServerManager* server = ServerManager::Instance(list);

    server->Run();

    ServerManager::Release();
    server = nullptr;

    return 0;
}
