#pragma once
#ifndef SERVER_HH
#define SERVER_HH

#include <iostream>
#include <memory>
#include <winsock2.h>
#include <thread>
#include <http.hh>
#include <string>

#define REQUEST_BUFFER 8192

extern std::string port; /*main.cc*/

class Server {
public:
    short port;
    Server(short port);
    ~Server();
    void start();
    _HTTP_REQUEST parse_http_request(const std::string& request);
private:
    void accept_connections();
    
    WSADATA wsa_data_;
    SOCKET listen_socket_;
    sockaddr_in server_addr_;
};




#endif // SERVER_HH
