#pragma once
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include "transport.h"
namespace s_rpc {
namespace transport{

class TCP_socket : public Transport {

public:

    TCP_socket();
    ~TCP_socket();

    bool TCP_connect(const std::string& host, int port);
    bool TCP_listen(int port);
    bool TCP_accept();
    bool send_data(const std::string& data);
    std::string receive_data();

private:

    int socket_fd;
    int recv_fd;
    sockaddr_in r_addr;
    socklen_t r_addr_len = sizeof(r_addr);
};

} //namespace transport
} //namespace s_rpc