#include <database.hh>
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

/*+++
CRYPTO MODEL
---*/
Crypto::Crypto() : id(0), price(0.0) {}

Crypto::Crypto(int id, const std::string& name, const std::string& symbol, double price)
    : id(id), name(name), symbol(symbol), price(price) {}

int Crypto::get_id() const { return id; }
void Crypto::set_id(int id) { this->id = id; }

std::string Crypto::get_name() const { return name; }
void Crypto::set_name(const std::string& name) { this->name = name; }

std::string Crypto::get_symbol() const { return symbol; }
void Crypto::set_symbol(const std::string& symbol) { this->symbol = symbol; }

double Crypto::get_price() const { return price; }
void Crypto::set_price(double price) { this->price = price; }

bool Crypto::save(Database& db) {
    std::string query = "INSERT INTO cryptos (name, symbol, price) VALUES ('" +
                        name + "', '" + symbol + "', " + std::to_string(price) + ");";
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
        crypto.set_symbol(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        crypto.set_price(sqlite3_column_double(stmt, 3));
    }
    sqlite3_finalize(stmt);
    return crypto;
}

/*+++
STOCK MODEL
---*/

Stock::Stock() : id(0), user_id(0), crypto_id(0), amount(0.0) {}

Stock::Stock(int id, int user_id, int crypto_id, double amount)
    : id(id), user_id(user_id), crypto_id(crypto_id), amount(amount) {}

// Getters and Setters
int Stock::get_id() const { return id; }
void Stock::set_id(int id) { this->id = id; }

int Stock::get_user_id() const { return user_id; }
void Stock::set_user_id(int user_id) { this->user_id = user_id; }

int Stock::get_crypto_id() const { return crypto_id; }
void Stock::set_crypto_id(int crypto_id) { this->crypto_id = crypto_id; }

double Stock::get_amount() const { return amount; }
void Stock::set_amount(double amount) { this->amount = amount; }

bool Stock::save(Database& db) {
    std::string query = "INSERT INTO stocks (user_id, crypto_id, amount) VALUES (" +
                        std::to_string(user_id) + ", " + std::to_string(crypto_id) + ", " + std::to_string(amount) + ");";
    return db.execute_query(query);
}


/*+++
TRANSACTION MODEL
---*/
Transaction::Transaction() : id(0), user_id(0), crypto_id(0), amount(0.0), price(0.0) {}

Transaction::Transaction(int id, int user_id, int crypto_id, double amount, double price, const std::string& type, const std::string& date)
    : id(id), user_id(user_id), crypto_id(crypto_id), amount(amount), price(price), type(type), date(date) {}

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
