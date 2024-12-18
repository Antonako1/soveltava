#include <database.hh>
#include <json.hpp>
/*+++
USER MODEL
---*/
User::User() : id(0), age(0), balance(0.0) {}

User::User(int id, const std::string& name, const std::string& email, int age, const std::string& password_hash, double balance)
    : id(id), name(name), email(email), age(age), password_hash(password_hash), balance(balance) {}

int User::get_id() const { return id; }
void User::set_id(int id) { this->id = id; }

std::string User::get_name() const { return name; }
void User::set_name(const std::string& name) { this->name = name; }

std::string User::get_email() const { return email; }
void User::set_email(const std::string& email) { this->email = email; }

int User::get_age() const { return age; }
void User::set_age(int age) { this->age = age; }

std::string User::get_password_hash() const { return password_hash; }
void User::set_password_hash(const std::string& password_hash) { this->password_hash = password_hash; }

double User::get_balance() const { return balance; }
void User::set_balance(double balance) { this->balance = balance; }

bool User::save(Database& db) {
    std::string query = "INSERT INTO users (name, email, age, password_hash, balance) VALUES ('" +
                        name + "', '" + email + "', " + std::to_string(age) + ", '" + password_hash + "', " + std::to_string(balance) + ");";
    return db.execute_query(query);
}

User User::find_by_id(Database& db, int user_id) {
    sqlite3_stmt* stmt;
    std::string query = "SELECT * FROM users WHERE id = " + std::to_string(user_id) + ";";
    sqlite3_prepare_v2(db.get_db(), query.c_str(), -1, &stmt, nullptr);

    User user;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        user.set_id(sqlite3_column_int(stmt, 0));
        user.set_name(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        user.set_email(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        user.set_age(sqlite3_column_int(stmt, 3));
        user.set_password_hash(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
        user.set_balance(sqlite3_column_double(stmt, 5));
    }
    sqlite3_finalize(stmt);
    return user;
}

User User::find_by_email(Database& db, const std::string& email) {
    sqlite3_stmt* stmt;
    std::string query = "SELECT * FROM users WHERE email = '" + email + "';";
    sqlite3_prepare_v2(db.get_db(), query.c_str(), -1, &stmt, nullptr);

    User user;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        user.set_id(sqlite3_column_int(stmt, 0));
        user.set_name(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        user.set_email(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        user.set_age(sqlite3_column_int(stmt, 3));
        user.set_password_hash(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
        user.set_balance(sqlite3_column_double(stmt, 5));
    }
    sqlite3_finalize(stmt);
    return user;
}

json User::to_json(){
    json j;
    j["id"] = id;
    j["name"] = name;
    j["email"] = email;
    j["age"] = age;
    j["balance"] = balance;
    j["password_hash"] = password_hash;
    return j;
};  

/*+++
CRYPTO MODEL
---*/
Crypto::Crypto() : id(0), price(0.0) {}

Crypto::Crypto(int id, const std::string& name, const std::string& tag, double price)
    : id(id), name(name), tag(tag), price(price) {}

int Crypto::get_id() const { return id; }
void Crypto::set_id(int id) { this->id = id; }

std::string Crypto::get_name() const { return name; }
void Crypto::set_name(const std::string& name) { this->name = name; }

std::string Crypto::get_tag() const { return tag; }
void Crypto::set_tag(const std::string& tag) { this->tag = tag; }

double Crypto::get_price() const { return price; }
void Crypto::set_price(double price) { this->price = price; }

bool Crypto::save(Database& db) {
    std::string query = "INSERT INTO cryptos (name, tag, price) VALUES ('" +
                        name + "', '" + tag + "', " + std::to_string(price) + ");";
    return db.execute_query(query);
}

Crypto Crypto::find_by_id(Database& db, int crypto_id) {
    sqlite3_stmt* stmt;
    std::string query = "SELECT * FROM cryptos WHERE id = " + std::to_string(crypto_id) + ";";
    sqlite3_prepare_v2(db.get_db(), query.c_str(), -1, &stmt, nullptr);

    Crypto crypto;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        crypto.set_id(sqlite3_column_int(stmt, 0));
        crypto.set_name(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        crypto.set_tag(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        crypto.set_price(sqlite3_column_double(stmt, 3));
    }
    sqlite3_finalize(stmt);
    return crypto;
}

Crypto Crypto::find_by_tag(Database& db, const std::string& tag) {
    sqlite3_stmt* stmt;
    std::string query = "SELECT * FROM cryptos WHERE tag = '" + tag + "';";
    sqlite3_prepare_v2(db.get_db(), query.c_str(), -1, &stmt, nullptr);

    Crypto crypto;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        crypto.set_id(sqlite3_column_int(stmt, 0));
        crypto.set_name(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        crypto.set_tag(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        crypto.set_price(sqlite3_column_double(stmt, 3));
    }
    sqlite3_finalize(stmt);
    return crypto;
}

std::vector<Crypto> Crypto::vector_find_by_user_id(Database& db, int user_id) {
    sqlite3_stmt* stmt;
    std::string query = "SELECT * FROM cryptos WHERE user_id = " + std::to_string(user_id) + ";";
    sqlite3_prepare_v2(db.get_db(), query.c_str(), -1, &stmt, nullptr);

    std::vector<Crypto> cryptos;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Crypto crypto;
        crypto.set_id(sqlite3_column_int(stmt, 0));
        crypto.set_name(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        crypto.set_tag(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        crypto.set_price(sqlite3_column_double(stmt, 3));
        cryptos.push_back(crypto);
    }
    sqlite3_finalize(stmt);
    return cryptos;
}

json Crypto::to_json(){
    json j;
    j["id"] = id;
    j["tag"] = tag;
    j["name"] = name;
    j["price"] = price;
    return j;
};

/*+++
STOCK MODEL
---*/
Stock::Stock() : id(0), tag(""), name(""), price(0.0) {}

Stock::Stock(int id, const std::string& tag, const std::string& name, double price)
    : id(id), tag(tag), name(name), price(price) {}

// Getters and Setters
int Stock::get_id() const { return id; }
void Stock::set_id(int id) { this->id = id; }

std::string Stock::get_tag() const { return tag; }
void Stock::set_tag(const std::string& tag) { this->tag = tag; }

std::string Stock::get_name() const { return name; }
void Stock::set_name(const std::string& name) { this->name = name; }

double Stock::get_price() const { return price; }
void Stock::set_price(double price) { this->price = price; }

bool Stock::save(Database& db) {
    std::string query = "INSERT INTO stocks (tag, name, price) VALUES ('" +
                        tag + "', '" + name + "', " + std::to_string(price) + ");";
    return db.execute_query(query);
}

std::vector<Stock> Stock::vector_find_by_user_id(Database& db, int user_id) {
    sqlite3_stmt* stmt;
    std::string query = "SELECT * FROM stocks WHERE user_id = " + std::to_string(user_id) + ";";
    sqlite3_prepare_v2(db.get_db(), query.c_str(), -1, &stmt, nullptr);

    std::vector<Stock> stocks;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Stock stock;
        stock.set_id(sqlite3_column_int(stmt, 0));
        stock.set_tag(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        stock.set_name(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        stock.set_price(sqlite3_column_double(stmt, 3));
        stocks.push_back(stock);
    }
    sqlite3_finalize(stmt);
    return stocks;
}

Stock Stock::find_by_id(Database& db, int stock_id) {
    sqlite3_stmt* stmt;
    std::string query = "SELECT * FROM stocks WHERE id = " + std::to_string(stock_id) + ";";
    sqlite3_prepare_v2(db.get_db(), query.c_str(), -1, &stmt, nullptr);

    Stock stock;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        stock.set_id(sqlite3_column_int(stmt, 0));
        stock.set_tag(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        stock.set_name(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        stock.set_price(sqlite3_column_double(stmt, 3));
    }
    sqlite3_finalize(stmt);
    return stock;
}

Stock Stock::find_by_tag(Database& db, const std::string& tag) {
    sqlite3_stmt* stmt;
    std::string query = "SELECT * FROM stocks WHERE tag = '" + tag + "';";
    sqlite3_prepare_v2(db.get_db(), query.c_str(), -1, &stmt, nullptr);

    Stock stock;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        stock.set_id(sqlite3_column_int(stmt, 0));
        stock.set_tag(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        stock.set_name(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        stock.set_price(sqlite3_column_double(stmt, 3));
    }
    sqlite3_finalize(stmt);
    return stock;
}

json Stock::to_json() {
    json j;
    j["id"] = id;
    j["tag"] = tag;
    j["name"] = name;
    j["price"] = price;
    return j;
};

/*+++
TRANSACTION MODEL
---*/
Transaction::Transaction() : id(0), user_id(0), crypto_id(0), amount(0.0), price(0.0) {}

Transaction::Transaction(int id, int user_id, int crypto_id, int stock_id, double amount, double price, const std::string& type, const std::string& date)
    : id(id), user_id(user_id), crypto_id(crypto_id), stock_id(stock_id), amount(amount), price(price), type(type), date(date) {}

// Getters and Setters
int Transaction::get_id() const { return id; }
void Transaction::set_id(int id) { this->id = id; }

int Transaction::get_user_id() const { return user_id; }
void Transaction::set_user_id(int user_id) { this->user_id = user_id; }

int Transaction::get_crypto_id() const { return crypto_id; }
void Transaction::set_crypto_id(int crypto_id) { this->crypto_id = crypto_id; }

double Transaction::get_amount() const { return amount; }
void Transaction::set_amount(double amount) { this->amount = amount; }

double Transaction::get_price() const { return price; }
void Transaction::set_price(double price) { this->price = price; }

int Transaction::get_stock_id() const {
    return stock_id;
}
void Transaction::set_stock_id(int stock_id) {
    this->stock_id = stock_id;
}

std::string Transaction::get_type() const { return type; }
void Transaction::set_type(const std::string& type) { this->type = type; }

std::string Transaction::get_date() const { return date; }
void Transaction::set_date(const std::string& date) { this->date = date; }

bool Transaction::save(Database& db) {
    std::string query = "INSERT INTO transactions (user_id, crypto_id, amount, price, type, date) VALUES (" +
                        std::to_string(user_id) + ", " + std::to_string(crypto_id) + ", " + std::to_string(amount) + ", " +
                        std::to_string(price) + ", '" + type + "', '" + date + "');";
    return db.execute_query(query);
}

Transaction Transaction::find_by_id(Database& db, int transaction_id) {
    sqlite3_stmt* stmt = nullptr;
    std::string query = "SELECT * FROM transactions WHERE id = ?;";
    Transaction transaction;

    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db.get_db(), query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error("Failed to prepare SQL statement: " + std::string(sqlite3_errmsg(db.get_db())));
    }

    try {
        // Bind the parameter
        if (sqlite3_bind_int(stmt, 1, transaction_id) != SQLITE_OK) {
            throw std::runtime_error("Failed to bind parameter: " + std::string(sqlite3_errmsg(db.get_db())));
        }

        // Execute the statement and process the result
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            transaction.set_id(sqlite3_column_int(stmt, 0));
            transaction.set_user_id(sqlite3_column_int(stmt, 1));
            transaction.set_crypto_id(sqlite3_column_int(stmt, 2));
            transaction.set_amount(sqlite3_column_double(stmt, 3));
            transaction.set_price(sqlite3_column_double(stmt, 4));

            const char* type = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
            transaction.set_type(type ? type : "");  // Handle NULL

            const char* date = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));
            transaction.set_date(date ? date : "");  // Handle NULL
        } else {
            throw std::runtime_error("Transaction not found for id: " + std::to_string(transaction_id));
        }
    } catch (...) {
        // Finalize the statement before rethrowing
        sqlite3_finalize(stmt);
        throw;
    }

    // Finalize the statement
    sqlite3_finalize(stmt);

    return transaction;
}


std::vector<Transaction> Transaction::vector_find_by_user_id(Database& db, int user_id){
    sqlite3_stmt* stmt;
    std::string query = "SELECT * FROM transactions WHERE user_id = " + std::to_string(user_id) + ";";
    sqlite3_prepare_v2(db.get_db(), query.c_str(), -1, &stmt, nullptr);

    std::vector<Transaction> transactions;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Transaction transaction;
        transaction.set_id(sqlite3_column_int(stmt, 0));
        transaction.set_user_id(sqlite3_column_int(stmt, 1));
        transaction.set_crypto_id(sqlite3_column_int(stmt, 2));
        transaction.set_amount(sqlite3_column_double(stmt, 3));
        transaction.set_price(sqlite3_column_double(stmt, 4));
        transaction.set_type(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));
        transaction.set_date(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)));
        transactions.push_back(transaction);
    }
    sqlite3_finalize(stmt);
    return transactions;
}

Transaction Transaction::find_by_user_id(Database& db, int user_id){
    sqlite3_stmt* stmt;
    std::string query = "SELECT * FROM transactions WHERE user_id = " + std::to_string(user_id) + ";";
    sqlite3_prepare_v2(db.get_db(), query.c_str(), -1, &stmt, nullptr);

    Transaction transaction;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        transaction.set_id(sqlite3_column_int(stmt, 0));
        transaction.set_user_id(sqlite3_column_int(stmt, 1));
        transaction.set_crypto_id(sqlite3_column_int(stmt, 2));
        transaction.set_amount(sqlite3_column_double(stmt, 3));
        transaction.set_price(sqlite3_column_double(stmt, 4));
        transaction.set_type(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));
        transaction.set_date(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)));
    }
    sqlite3_finalize(stmt);
    return transaction;
}
Transaction Transaction::find_by_crypto_id(Database& db, int crypto_id){
    sqlite3_stmt* stmt;
    std::string query = "SELECT * FROM transactions WHERE crypto_id = " + std::to_string(crypto_id) + ";";
    sqlite3_prepare_v2(db.get_db(), query.c_str(), -1, &stmt, nullptr);

    Transaction transaction;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        transaction.set_id(sqlite3_column_int(stmt, 0));
        transaction.set_user_id(sqlite3_column_int(stmt, 1));
        transaction.set_crypto_id(sqlite3_column_int(stmt, 2));
        transaction.set_amount(sqlite3_column_double(stmt, 3));
        transaction.set_price(sqlite3_column_double(stmt, 4));
        transaction.set_type(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));
        transaction.set_date(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)));
    }
    sqlite3_finalize(stmt);
    return transaction;
}
Transaction Transaction::find_by_stock_id(Database& db, int stock_id){
    sqlite3_stmt* stmt;
    std::string query = "SELECT * FROM transactions WHERE stock_id = " + std::to_string(stock_id) + ";";
    sqlite3_prepare_v2(db.get_db(), query.c_str(), -1, &stmt, nullptr);

    Transaction transaction;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        transaction.set_id(sqlite3_column_int(stmt, 0));
        transaction.set_user_id(sqlite3_column_int(stmt, 1));
        transaction.set_crypto_id(sqlite3_column_int(stmt, 2));
        transaction.set_amount(sqlite3_column_double(stmt, 3));
        transaction.set_price(sqlite3_column_double(stmt, 4));
        transaction.set_type(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));
        transaction.set_date(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)));
    }
    sqlite3_finalize(stmt);
    return transaction;
}

json Transaction::to_json(){
    json j;
    j["id"] = id;
    j["user_id"] = user_id;
    j["crypto_id"] = crypto_id;
    j["stock_id"] = stock_id;
    j["amount"] = amount;
    j["price"] = price;
    j["type"] = type;
    j["date"] = date;
    return j;
};
