#pragma once
#include <string>

namespace s_rpc {
namespace transport{

class TCP_socket{

public:

    TCP_socket();
    ~TCP_socket();

    bool connect(const std::string& host, int port);
    bool listen(int port);
    int send(const std::string& data);
    std::string receive();

private:

    int socket_fd;

};

} //namespace transport
} //namespace s_rpc