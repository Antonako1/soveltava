#include <http.hh>
#include <string>

// Function to create the HTTP header with the provided content length and content type
_HTTP_HEADER create_full_http_header(
    const std::string& content_length,
    HTTP_CONTENT_TYPE content_type,
    const std::string& connection,
    const std::string& host
)
{
    std::string content_type_str = "";
    switch (content_type)
    {
    case HTTP_CONTENT_TYPE::TEXT_HTML:
        content_type_str = "text/html";
        break;
    case HTTP_CONTENT_TYPE::TEXT_PLAIN:
        content_type_str = "text/plain";
        break;
    case HTTP_CONTENT_TYPE::APPLICATION_JSON:
        content_type_str = "application/json";
        break;
    }

    _HTTP_HEADER http_header(
        content_type_str,
        content_length, 
        connection,
        host
        );
    return http_header;
}

// Function to create the HTTP request with the provided parameters
_HTTP_RESPONSE create_full_HTTP_RESPONSE(
    HTTP_STATUS_CODE status_code,
    HTTP_VERSION version,
    HTTP_METHOD method,
    _HTTP_HEADER headers,
    const std::string& body,
    const std::string& path
)
{
    std::string status_code_str = "";
    std::string version_str = "";
    std::string method_str = "";

    switch (status_code)
    {
    case HTTP_STATUS_CODE::OK:
        status_code_str = "200 OK";
        break;
    case HTTP_STATUS_CODE::BAD_REQUEST:
        status_code_str = "400 Bad Request";
        break;
    case HTTP_STATUS_CODE::NOT_FOUND:
        status_code_str = "404 Not Found";
        break;
    case HTTP_STATUS_CODE::INTERNAL_SERVER_ERROR:
        status_code_str = "500 Internal Server Error";
        break;
    }

    switch (version)
    {
    case HTTP_VERSION::HTTP_1_0:
        version_str = "HTTP/1.0";
        break;
    case HTTP_VERSION::HTTP_1_1:
        version_str = "HTTP/1.1";
        break;
    }

    switch (method)
    {
    case HTTP_METHOD::GET:
        method_str = "GET";
        break;
    case HTTP_METHOD::POST:
        method_str = "POST";
        break;
    case HTTP_METHOD::PUT:
        method_str = "PUT";
        break;
    }

    _HTTP_RESPONSE HTTP_RESPONSE(
        method_str,
        path,
        version_str,
        headers,
        body,
        status_code_str
    );

    return HTTP_RESPONSE;
}

// Function to create the HTTP request with the provided parameters
_HTTP_RESPONSE create_full_HTTP_RESPONSE_wide_params(
    HTTP_STATUS_CODE status_code,
    HTTP_VERSION version,
    HTTP_METHOD method,
    const std::string& body,
    HTTP_CONTENT_TYPE content_type,
    const std::string& path,
    const std::string& connection,
    const std::string& host
)
{
    std::string content_length = std::to_string(body.size() - 1);
    _HTTP_HEADER headers = create_full_http_header(content_length, content_type, connection, host);

    _HTTP_RESPONSE HTTP_RESPONSE = create_full_HTTP_RESPONSE(
        status_code,
        version,
        method,
        headers,
        body,
        path
    );

    return HTTP_RESPONSE;
}
