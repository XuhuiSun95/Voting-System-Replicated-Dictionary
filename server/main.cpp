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
    int id, size;
    std::string ipaddr;
    int port;
    int count = 0;

    while(std::getline(ifs, s)) {
        
        count++;
        if(count>3) {
            std::cerr << "Invalid configuration file!" << std::endl;
            std::cerr << "Conf format:" << std::endl;
            std::cerr << "<Server ID> <Number of Server>" << std::endl;
            std::cerr << "<Local Address> <Local Port>" << std::endl;
            std::cerr << "<Send address> <Send port>" << std::endl;

            ifs.close();
            return 1;
        }

        std::istringstream iss(s);
        if(count==1) {
            iss >> id;
            iss >> size;
        }
        else {
            iss >> ipaddr;
            iss >> port;
            list.push_back(std::make_pair(ipaddr, port));
        }
    }

    ifs.close();

    if(count!=3) {
        std::cerr << "Unmatched input!" << std::endl; 
        std::cerr << "Conf format:" << std::endl;
        std::cerr << "<Server ID> <Number of Server>" << std::endl;
        std::cerr << "<Local Address> <Local Port>" << std::endl;
        std::cerr << "<Send address> <Send port>" << std::endl;

        return 1;
    }

    ServerManager* server = ServerManager::Instance(id, size, list);

    server->Run();

    ServerManager::Release();
    server = nullptr;

    return 0;
}
