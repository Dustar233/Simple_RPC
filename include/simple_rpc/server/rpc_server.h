#pragma once
#include <string>
#include <functional>
#include <map>

namespace s_rpc {

class RPC_server{

public:

    RPC_server(int port);
    void register_method(const std::string& name, std::function<std::string(std::string)> handler);
    void run();

private:

    int port;
    std::map<std::string, std::function<std::string(std::string)>> methods;

};

} //namespace s_rpc