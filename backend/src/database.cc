#include "database.hh"
#include <fstream>
#include <sstream>

Database::Database() : db(nullptr) {}

bool Database::open(const std::string& db_name) {
    if (sqlite3_open(db_name.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    return true;
}

bool Database::delete_database(const std::string& db_name) {
    if (std::remove(db_name.c_str()) != 0) {
        std::cerr << "Error deleting database!" << std::endl;
        return false;
    }
    return true;
}

void Database::close() {
    if (db) {
        sqlite3_close(db);
        db = nullptr;
    }
}

sqlite3* Database::get_db() {
    return db;
}

Database::~Database() {
    close();
}


bool Database::create_database(const std::string& db_name) {
    if (sqlite3_open(db_name.c_str(), &this->db) != SQLITE_OK) {
        std::cerr << "Failed to create SQLite database: " << sqlite3_errmsg(this->db) << std::endl;
        return false;
    }
    return true;
}


bool Database::execute_query(const std::string& sql) {
    char* errorMessage = nullptr;
    if (sqlite3_exec(this->db, sql.c_str(), nullptr, nullptr, &errorMessage) != SQLITE_OK) {
        std::cerr << "Error executing SQL: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
        return false;
    }
    return true;
}


void Database::create_tables() {
    const char* create_user_table = R"(
        CREATE TABLE IF NOT EXISTS User (
            id INTEGER PRIMARY KEY,
            name TEXT NOT NULL,
            email TEXT NOT NULL,
            age INTEGER NOT NULL,
            password_hash TEXT NOT NULL,
            balance REAL NOT NULL
        );
    )";

    const char* create_crypto_table = R"(
        CREATE TABLE IF NOT EXISTS Crypto (
            id INTEGER PRIMARY KEY,
            name TEXT NOT NULL,
            symbol TEXT NOT NULL,
            price REAL NOT NULL
        );
    )";

    const char* create_stock_table = R"(
        CREATE TABLE IF NOT EXISTS Stock (
            id INTEGER PRIMARY KEY,
            user_id INTEGER NOT NULL,
            crypto_id INTEGER NOT NULL,
            amount REAL NOT NULL,
            FOREIGN KEY (user_id) REFERENCES User(id),
            FOREIGN KEY (crypto_id) REFERENCES Crypto(id)
        );
    )";

    const char* create_transaction_table = R"(
        CREATE TABLE IF NOT EXISTS transactions (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            user_id INTEGER NOT NULL,
            crypto_id INTEGER NOT NULL,
            amount REAL NOT NULL,
            price REAL NOT NULL,
            type TEXT NOT NULL CHECK(type IN ('buy', 'sell')),
            date TEXT DEFAULT CURRENT_TIMESTAMP,
            FOREIGN KEY (user_id) REFERENCES User(id),
            FOREIGN KEY (crypto_id) REFERENCES Crypto(id)
        );
    )";

    char* error_message = nullptr;

    if (sqlite3_exec(db, create_user_table, nullptr, nullptr, &error_message) != SQLITE_OK) {
        std::cerr << "Error creating User table: " << error_message << std::endl;
        sqlite3_free(error_message);
    }

    if (sqlite3_exec(db, create_crypto_table, nullptr, nullptr, &error_message) != SQLITE_OK) {
        std::cerr << "Error creating Crypto table: " << error_message << std::endl;
        sqlite3_free(error_message);
    }

    if (sqlite3_exec(db, create_stock_table, nullptr, nullptr, &error_message) != SQLITE_OK) {
        std::cerr << "Error creating Stock table: " << error_message << std::endl;
        sqlite3_free(error_message);
    }

    if (sqlite3_exec(db, create_transaction_table, nullptr, nullptr, &error_message) != SQLITE_OK) {
        std::cerr << "Error creating Transaction table: " << error_message << std::endl;
        sqlite3_free(error_message);
    }
}

void Database::insert_sample_data() {
    const char* insert_user = R"(
        INSERT INTO User (id, name, email, age, password_hash, balance)
        VALUES (1, 'John Doe', 'john.doe@example.com', 30, 'hashed_password', 1000.50);
    )";

    const char* insert_crypto = R"(
        INSERT INTO Crypto (id, name, symbol, price)
        VALUES (1, 'Bitcoin', 'BTC', 50000.00);
    )";

    const char* insert_stock = R"(
        INSERT INTO Stock (id, user_id, crypto_id, amount)
        VALUES (1, 1, 1, 0.02);
    )";

    const char* insert_transaction = R"(
        INSERT INTO transactions (id, user_id, crypto_id, amount, price, type, date)
        VALUES (1, 1, 1, 0.01, 50000.00, 'buy', '2024-12-17');
    )";

    char* error_message = nullptr;

    if (sqlite3_exec(db, insert_user, nullptr, nullptr, &error_message) != SQLITE_OK) {
        std::cerr << "Error inserting into User table: " << error_message << std::endl;
        sqlite3_free(error_message);
    }

    if (sqlite3_exec(db, insert_crypto, nullptr, nullptr, &error_message) != SQLITE_OK) {
        std::cerr << "Error inserting into Crypto table: " << error_message << std::endl;
        sqlite3_free(error_message);
    }

    if (sqlite3_exec(db, insert_stock, nullptr, nullptr, &error_message) != SQLITE_OK) {
        std::cerr << "Error inserting into Stock table: " << error_message << std::endl;
        sqlite3_free(error_message);
    }

    if (sqlite3_exec(db, insert_transaction, nullptr, nullptr, &error_message) != SQLITE_OK) {
        std::cerr << "Error inserting into Transaction table: " << error_message << std::endl;
        sqlite3_free(error_message);
    }
}

