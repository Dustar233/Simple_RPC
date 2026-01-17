#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "simple_rpc/transport/TCP_socket.h"

#define MAXSIZE 1024

namespace s_rpc {
namespace transport{

TCP_socket::TCP_socket(){
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
}
TCP_socket::~TCP_socket(){
    close(socket_fd);
}

bool TCP_socket::TCP_connect(const std::string& host, int port){
    
    sockaddr_in s_addr;
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(port); 
    if(inet_pton(AF_INET, host.c_str(), &s_addr.sin_addr) <= 0){
        return 0; 
    }
    if(connect(socket_fd, (sockaddr*)&s_addr, sizeof(s_addr)) < 0){
        return 0;
    }
    return 1;
}

bool TCP_socket::TCP_listen(int port){
    sockaddr_in s_addr;
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(port);
    s_addr.sin_addr.s_addr = INADDR_ANY;
    if(bind(socket_fd, (sockaddr*)&s_addr, sizeof(s_addr)) < 0){
        return 0; 
    }
    if(listen(socket_fd, 3) < 0){
        return 0;
    }
    return 1;
}

bool TCP_socket::send_data(const std::string& data){
    if(send(socket_fd, data.c_str(), data.size(), 0) < 0){
        return 0;
    }
    return 1;
}

bool TCP_socket::TCP_accept(){
    
    recv_fd = accept(socket_fd, (sockaddr*)&r_addr, &r_addr_len);
    if(recv_fd < 0){
        return 0;
    }
    return 1;

}

std::string TCP_socket::receive_data(){

    char buffer[MAXSIZE]{0};
    ssize_t recv_data_len;
    if(!recv_fd){
        return "";
    }
    recv_data_len = read(recv_fd, buffer, MAXSIZE);
    if(recv_data_len <= 0){
        return "";
    }
    std::string data(buffer,recv_data_len); 
    return data;
}

}
}