#pragma once
#ifndef HTTP_HH
#define HTTP_HH

#include <string>
#include <map>

// #ifdef __cplusplus
// extern "C" {
// #endif

enum class HTTP_STATUS_CODE {
    OK = 200,  // Standard OK response
    BAD_REQUEST = 400,  // The request could not be understood by the server
    NOT_FOUND = 404,  // Resource not found on the server
    INTERNAL_SERVER_ERROR = 500  // General server error
};

enum class HTTP_VERSION {
    HTTP_1_0 = 0x0001,  // HTTP 1.0 version
    HTTP_1_1 = 0x0002   // HTTP 1.1 version
};

enum class HTTP_METHOD {
    GET = 0x0001,   // GET method, typically used for fetching resources
    POST = 0x0002,  // POST method, used for sending data to the server
    PUT = 0x0004    // PUT method, used to update an existing resource
};

enum class HTTP_HEADER {
    CONTENT_TYPE = 0x0001,   // Content-Type header, indicating the type of the content
    CONTENT_LENGTH = 0x0002  // Content-Length header, specifying the length of the content in bytes
};

enum class HTTP_CONTENT_TYPE {
    TEXT_HTML = 0x0001,       // Content type: text/html
    TEXT_PLAIN = 0x0002,      // Content type: text/plain
    APPLICATION_JSON = 0x0004 // Content type: application/json
};


#pragma pack(push, 1)
typedef struct _HTTP_HEADER {
    std::string content_type;   // The content type of the response, e.g., "text/html"
    std::string content_length; // The content length of the response, e.g., "1234" (as a string)
    std::string connection;     // The connection type of the response, e.g., "close"
    std::string host;           // The host of the response, e.g., "localhost"
    _HTTP_HEADER() : content_type(""), content_length("") {}

    _HTTP_HEADER(
        const std::string& _content_type,
        const std::string& _content_length,
        const std::string& _connection,
        const std::string& _host
    ) : content_type(_content_type), 
    content_length(_content_length),
    connection(_connection),
    host(_host)
    {}


    // Converts the header information to a formatted string
    inline std::string format_to_string() const {
        std::string headers = "";
        if (!content_type.empty()) {
            headers += "Content-Type: " + content_type + "\r\n";
        }
        if (!content_length.empty()) {
            headers += "Content-Length: " + content_length + "\r\n";
        }
        if (!connection.empty()) {
            headers += "Connection: " + connection + "\r\n";
        }
        if(!host.empty()) {
            headers += "Host: " + host + "\r\n";
        }
        return headers;
    }

    // Converts the header information to a C-style string
    inline const char* format_and_to_c_str() const {
        static std::string formatted_headers;
        formatted_headers = format_to_string();
        return formatted_headers.c_str();
    }
} _HTTP_HEADER, *P_HTTP_HEADER;


typedef struct _HTTP_REQUEST {
    std::string method;
    std::string url;
    std::string version;
    std::map<std::string, std::string> headers;
    std::string body;

    _HTTP_REQUEST() : method(""), url(""), version(""), headers(std::map<std::string, std::string>()), body("") {}

    _HTTP_REQUEST(
        const std::string& _method,
        const std::string& _url,
        const std::string& _version,
        const std::map<std::string, std::string>& _headers,
        const std::string& _body
    ) : method(_method), url(_url), version(_version), headers(_headers), body(_body) {}
} _HTTP_REQUEST, *P_HTTP_REQUEST;


typedef struct _HTTP_RESPONSE {
    std::string method;     // HTTP method (GET, POST, etc.)
    std::string path;       // Request path (e.g., "/index.html")
    std::string version;    // HTTP version (e.g., "HTTP/1.1")
    _HTTP_HEADER headers;   // Request headers (e.g., Content-Type, Content-Length, etc.)
    std::string body;       // Body content, used primarily in POST/PUT requests
    std::string status_code; // Status code of the response

    // Default constructor with an empty request
    _HTTP_RESPONSE() 
        : method(""), path(""), version(""), headers(_HTTP_HEADER()), body(""), status_code("") {}

    _HTTP_RESPONSE(
        /*
        Contains the HTTP method of the request.
        For example, GET, POST, PUT, etc.
        */
        const std::string& _method,

        /*
        Contains the path of the request.
        For example, "/index.html"
        */
        const std::string& _path,

        /*  
        Contains the version of the request.
        For example, "HTTP/1.1"
        */
        const std::string& _version,

        /*
        Contains the headers of the request.
        _HTTP_HEADER object which can include content type, length, etc.
        */
        const _HTTP_HEADER _headers,

        /*
        Contains the body of the request.
        Used primarily for POST, PUT, or similar requests that send data.
        */
        const std::string& _body,

        /*
        Contains the status code of the response.
        For example, "200 OK", "404 Not Found", etc.
        */
        const std::string& _status_code
    )
        : method(_method), path(_path), version(_version), headers(_headers), body(_body), status_code(_status_code) {}

    // Converts the request to a formatted string
    inline std::string format_to_string() const {
        // method + " " + path + " " + version + " " + status_code + "\r\n";
        std::string request = version + " " + status_code + "\r\n";
        std::string headers = this->headers.format_to_string();
        request += headers;

        if (!body.empty()) {
            request += "\r\n" + body;
        }
        return request;
    }


    // Converts the request to a C-style string
    inline const char* format_and_to_c_str() const {
        static std::string formatted_request;
        formatted_request = format_to_string();
        return formatted_request.c_str();
    }

    // Returns the length of the request
    inline size_t req_length() const {
        return format_to_string().length();
    }
} _HTTP_RESPONSE, *P_HTTP_RESPONSE;


#pragma pack(pop)

_HTTP_HEADER 
create_full_http_header
(
    const std::string& content_length,
    HTTP_CONTENT_TYPE content_type,
    const std::string& connection,
    const std::string& host
);

_HTTP_RESPONSE 
create_full_HTTP_RESPONSE
(
    HTTP_STATUS_CODE status_code,
    HTTP_VERSION version,
    HTTP_METHOD method,
    _HTTP_HEADER headers,
    const std::string &body,
    const std::string& path
);

_HTTP_RESPONSE 
create_full_HTTP_RESPONSE_wide_params(
    HTTP_STATUS_CODE status_code,
    HTTP_VERSION version,
    HTTP_METHOD method,
    const std::string& body,
    HTTP_CONTENT_TYPE content_type,
    const std::string& path,
    const std::string& connection,
    const std::string& host
);


// #ifdef __cplusplus
// }
// #endif

#endif // HTTP_HH