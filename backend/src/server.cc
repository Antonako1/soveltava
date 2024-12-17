#include <server.hh>
#include <http.hh>
#include <string>
#include <sstream>
#include <iostream>


_HTTP_REQUEST Server::parse_http_request(const std::string& request) {
    std::istringstream stream(request);
    _HTTP_REQUEST http_request;

    std::getline(stream, http_request.method, ' ');
    std::getline(stream, http_request.url, ' ');
    std::getline(stream, http_request.version);
    http_request.version.pop_back();

    // Parse the headers
    std::string header_line;
    while (std::getline(stream, header_line) && header_line != "\r") {
        size_t colon_pos = header_line.find(':');
        if (colon_pos != std::string::npos) {
            std::string key = header_line.substr(0, colon_pos);
            std::string value = header_line.substr(colon_pos + 1);
            value.erase(0, value.find_first_not_of(" "));
            value.pop_back();//last \r off
            http_request.headers[key] = value;
        }
    }

    //parse the body
    std::string body_line;
    while (std::getline(stream, body_line)) {
        http_request.body += body_line + "\n";
    }

    return http_request;
}



Server::Server(short port) {
    this->port = port;

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa_data_) != 0) {
        throw std::runtime_error("WSAStartup failed");
    }

    // Create a socket
    listen_socket_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listen_socket_ == INVALID_SOCKET) {
        WSACleanup();
        throw std::runtime_error("Socket creation failed");
    }

    // Set up the server address
    server_addr_.sin_family = AF_INET;
    server_addr_.sin_port = htons(port);
    server_addr_.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the address
    if (bind(listen_socket_, reinterpret_cast<SOCKADDR*>(&server_addr_), sizeof(server_addr_)) == SOCKET_ERROR) {
        closesocket(listen_socket_);
        WSACleanup();
        throw std::runtime_error("Bind failed");
    }

    // Listen for incoming connections
    if (listen(listen_socket_, SOMAXCONN) == SOCKET_ERROR) {
        closesocket(listen_socket_);
        WSACleanup();
        throw std::runtime_error("Listen failed");
    }
}

Server::~Server() {
    closesocket(listen_socket_);
    WSACleanup();
}

void Server::start() {
    std::cout << "Server started. Listening on port " << this->port << "..." << std::endl;
    accept_connections();
}

void Server::accept_connections() {
    while (true) {
        SOCKET client_socket = accept(listen_socket_, nullptr, nullptr);
        if (client_socket == INVALID_SOCKET) {
            std::cerr << "Accept failed with error: " << WSAGetLastError() << std::endl;
            continue;
        }

        char buffer[4096] = {0};
        int bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
        if (bytes_received == SOCKET_ERROR) {
            std::cerr << "Error receiving data: " << WSAGetLastError() << std::endl;
            closesocket(client_socket);
            continue;
        }
        std::cout << "New connection established." << std::endl;

        // parse request
        std::string request_data(buffer, bytes_received);
        _HTTP_REQUEST http_request = parse_http_request(request_data);

        std::cout << "\nRequest received:" << std::endl;
        std::cout << "Method: " << http_request.method << "\n"
                  << "URL: " << http_request.url << "\n"
                  << "Version: " << http_request.version << "\n";
        for (const auto& [key, value] : http_request.headers) {
            std::cout << key << ": " << value << "\n";
        }
        std::cout << "Body: " << http_request.body << "\n";
        std::cout << "Request parsed.\n" << std::endl;

        _HTTP_RESPONSE request = create_full_HTTP_RESPONSE_wide_params(
            HTTP_STATUS_CODE::OK,
            HTTP_VERSION::HTTP_1_1,
            HTTP_METHOD::GET,
            "Hello, World!",
            HTTP_CONTENT_TYPE::TEXT_HTML,
            "/",
            "close",
            "localhost:"+std::to_string(this->port)
        );
        std::cout << "\nResponse to send:" << std::endl;
        std::cout << request.format_to_string() << std::endl;
        std::cout << std::endl;
        size_t total_sent = 0;
        while (total_sent < request.req_length()) {
            size_t sent_bytes = send(client_socket, request.format_and_to_c_str() + total_sent, request.req_length() - total_sent, 0);
            if (sent_bytes == SOCKET_ERROR) {
                std::cerr << "Failed to send response with error: " << WSAGetLastError() << std::endl;
                break;
            }
            total_sent += sent_bytes;
        }
       
        std::cout << "Response sent. " << total_sent << " bytes sent out of " << request.req_length() << " bytes." << std::endl;

        // std::string response =
        //     "HTTP/1.1 200 OK\r\n"
        //     "Content-Type: text/html\r\n"
        //     "Content-Length: 12\r\n"
        //     "Connection: close\r\n"
        //     "Host: localhost:9090\r\n"
        //     "\r\n"
        //     "Hello, World!";


        // Close the client socket after communication
        closesocket(client_socket);
    }
}
