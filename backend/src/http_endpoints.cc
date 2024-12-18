#include <http.hh>
#include <database.hh>
#include <json.hpp>
#include <server.hh>
#include <crypt.hh>
#define INCLUDE_ATRC_STDLIB 1
#include <ATRC.hpp>
using json = nlohmann::json;

/*
Body: {
    "firstName":"test",
    "lastName":"test",
    "email":"gmail@gmail.com",
    "age":"100",
    "password":"J&\"2MH_m+4~dWws"
    }
*/
void register_endpoint(_HTTP_REQUEST& request, _HTTP_RESPONSE& response) {
    try {
        json body = json::parse(request.body);

        std::string name = body.at("firstName").get<std::string>() + ";" + body.at("lastName").get<std::string>();
        std::string email = body.at("email").get<std::string>();
        std::string __age = body.at("age").get<std::string>();
        std::string password = body.at("password").get<std::string>();
        double balance = 1000.f;

        int age = std::stoi(__age);
        try {
            age = std::stoi(__age);
        } catch (const std::invalid_argument& e) {
            std::cerr << e.what() << std::endl;
            throw std::runtime_error("Invalid age: not a number");
        } catch (const std::out_of_range& e) {
            std::cerr << e.what() << std::endl;
            throw std::runtime_error("Invalid age: out of range");
        }

        db.open(db.db_name);

        User user(0, name, email, age, password, balance);
        bool res = user.save(db);
        if(!res) {
            throw std::runtime_error("Failed to save user. User already exists or data is invalid.");
        }
        
        db.close();

        if(verbose)std::cout << "User registered: " << user.to_json().dump() << std::endl;
        response = create_full_HTTP_RESPONSE_wide_params(
            HTTP_STATUS_CODE::OK,
            HTTP_VERSION::HTTP_1_1,
            HTTP_METHOD::POST,
            user.to_json().dump(),
            HTTP_CONTENT_TYPE::APPLICATION_JSON,
            "/register",
            "close",
            "localhost:"+port
        );
    } catch (const std::exception& e) {
        response = create_full_HTTP_RESPONSE_wide_params(
            HTTP_STATUS_CODE::INTERNAL_SERVER_ERROR,
            HTTP_VERSION::HTTP_1_1,
            HTTP_METHOD::POST,
            "Failed to register user",
            HTTP_CONTENT_TYPE::TEXT_PLAIN,
            "/register",
            "close",
            "localhost:"+port
        );
        std::cerr << "Failed to register user: " << e.what() << std::endl;
    }
}
/*
body:
{
    "email":
    "password":
    "token":
}
*/
void login_endpoint(_HTTP_REQUEST& request, _HTTP_RESPONSE& response) {
    try {
        // Parse incoming JSON request
        json body = json::parse(request.body);
        std::string email = body.at("email").get<std::string>();
        std::string password = body.at("password").get<std::string>();
        std::string token = body.at("token").get<std::string>();
        db.open(db.db_name);

        User user = User::find_by_email(db, email);
        if (user.get_id() == 0) {
            throw std::runtime_error("User not found. Register first.");
        }

        db.close();

        std::string auth_token = generate_auth_token(user);
        if(auth_token != token) {
            json res = {
                {"password", user.get_password_hash()},
                {"token", auth_token},
                {"email", email},
                {"id", user.get_id()}
            };
            response = create_full_HTTP_RESPONSE_wide_params(
                HTTP_STATUS_CODE::UNAUTHORIZED,
                HTTP_VERSION::HTTP_1_1,
                HTTP_METHOD::POST,
                res.dump(),
                HTTP_CONTENT_TYPE::TEXT_PLAIN,
                "/login",
                "close",
                "localhost:" + port
            );
            return;
        }

        json response_data = {
            user.to_json(),
            {"token", auth_token}
        };

        response = create_full_HTTP_RESPONSE_wide_params(
            HTTP_STATUS_CODE::OK,
            HTTP_VERSION::HTTP_1_1,
            HTTP_METHOD::POST,
            response_data.dump(),
            HTTP_CONTENT_TYPE::APPLICATION_JSON,
            "/login",
            "close",
            "localhost:" + port
        );

        if (verbose) {
            std::cout << "User logged in: " << user.to_json().dump() << std::endl;
        }
    } catch (const std::exception& e) {
        // Handle errors and respond with an appropriate message
        response = create_full_HTTP_RESPONSE_wide_params(
            HTTP_STATUS_CODE::OK,
            HTTP_VERSION::HTTP_1_1,
            HTTP_METHOD::POST,
            e.what(),
            HTTP_CONTENT_TYPE::TEXT_PLAIN,
            "/login",
            "close",
            "localhost:" + port
        );
        std::cerr << "Failed to login user: " << e.what() << std::endl;
    }
}


void verify_endpoint(_HTTP_REQUEST& request, _HTTP_RESPONSE& response) {
    try {

    } catch (const std::exception& e) {
        std::cerr << "Failed to verify user: " << e.what() << std::endl;
    }
}

void refresh_endpoint(_HTTP_REQUEST& request, _HTTP_RESPONSE& response) {
    try {

    } catch (const std::exception& e) {
        std::cerr << "Failed to refresh user: " << e.what() << std::endl;
    }
}

void update_endpoint(_HTTP_REQUEST& request, _HTTP_RESPONSE& response) {
    try {

    } catch (const std::exception& e) {
        std::cerr << "Failed to update user: " << e.what() << std::endl;
    }
}

void delete_endpoint(_HTTP_REQUEST& request, _HTTP_RESPONSE& response) {
    try {

    } catch (const std::exception& e) {
        std::cerr << "Failed to delete user: " << e.what() << std::endl;
    }
}

void get_endpoint(_HTTP_REQUEST& request, _HTTP_RESPONSE& response) {
    try {
        json body = json::parse(request.body);
        std::string email = body.at("email").get<std::string>();

        db.open(db.db_name);

        User user = User::find_by_email(db, email);
        if (user.get_id() == 0) {
            throw std::runtime_error("User not found. Register first.");
        }

        Transaction test = Transaction::find_by_id(db, 1);
        std::cout << test.get_id() << " " << test.get_user_id() << " " << test.get_crypto_id() << " " << test.get_stock_id() << " " << test.get_amount() << " " << test.get_price() << " " << test.get_type() << " " << test.get_date() << std::endl;

        std::vector<Transaction> transactions = Transaction::vector_find_by_user_id(db, user.get_id());
        std::vector<Stock> stocks = Stock::vector_find_by_user_id(db, user.get_id());
        std::vector<Crypto> cryptos = Crypto::vector_find_by_user_id(db, user.get_id());

        json user_json = {
            {"user", user.to_json()},
            {"transactions", json::array()},
            {"stocks", json::array()},
            {"cryptos", json::array()}
        };

        for (Transaction& transaction : transactions) {
            user_json["transactions"].push_back(transaction.to_json());
        }
        for (Stock& stock : stocks) {
            user_json["stocks"].push_back(stock.to_json());
        }
        for (Crypto& crypto : cryptos) {
            user_json["cryptos"].push_back(crypto.to_json());
        }

        // Create and send the HTTP response
        response = create_full_HTTP_RESPONSE_wide_params(
            HTTP_STATUS_CODE::OK,
            HTTP_VERSION::HTTP_1_1,
            HTTP_METHOD::POST,
            user_json.dump(),
            HTTP_CONTENT_TYPE::APPLICATION_JSON,
            "/get",
            "close",
            "localhost:" + port
        );

        // Close the database connection
        db.close();

    } catch (const std::exception& e) {
        // Handle exceptions and send error response
        std::cerr << "Failed to get user: " << e.what() << std::endl;
        response = create_full_HTTP_RESPONSE_wide_params(
            HTTP_STATUS_CODE::INTERNAL_SERVER_ERROR,
            HTTP_VERSION::HTTP_1_1,
            HTTP_METHOD::POST,
            e.what(),
            HTTP_CONTENT_TYPE::TEXT_PLAIN,
            "/get",
            "close",
            "localhost:" + port
        );
    }
}
