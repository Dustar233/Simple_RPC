#pragma once
#include <string>

namespace s_rpc {

class RPC_client{

public:

    RPC_client(const std::string& host, int port);
    std::string call(const std::string& method_name, const std::string& args);

private:

    int port; 
    std::string host;

};

} // namespace s_rpc
