#pragma once
#ifndef DATABASE_HH
#define DATABASE_HH

#include <sqlite3.h>
#include <iostream>
#include <string>
#include <vector>

class Database {
protected:
    sqlite3* db;

public:
    Database();

    bool open(const std::string& db_name);

    void close();

    ~Database();

    bool execute_query(const std::string& sql);

    sqlite3* get_db();

    bool create_database(const std::string& db_name);

    bool delete_database(const std::string& db_name);

    void Database::insert_sample_data();
    void Database::create_tables();
};


/*+++
USER MODEL
---*/
class User {
private:
    int id;
    std::string name;
    std::string email;
    int age;
    std::string password_hash;
    double balance;

public:
    User();
    User(int id, const std::string& name, const std::string& email, int age, const std::string& password_hash, double balance);
    
    // Getters and Setters
    int get_id() const;
    void set_id(int id);
    
    std::string get_name() const;
    void set_name(const std::string& name);
    
    std::string get_email() const;
    void set_email(const std::string& email);
    
    int get_age() const;
    void set_age(int age);
    
    std::string get_password_hash() const;
    void set_password_hash(const std::string& password_hash);
    
    double get_balance() const;
    void set_balance(double balance);

    bool save(Database& db);
    static User find_by_id(Database& db, int user_id);
};

/*+++
CRYPTO MODEL
---*/
class Crypto {
private:
    int id;
    std::string name;
    std::string symbol;
    double price;

public:
    Crypto();
    Crypto(int id, const std::string& name, const std::string& symbol, double price);
    
    // Getters and Setters
    int get_id() const;
    void set_id(int id);
    
    std::string get_name() const;
    void set_name(const std::string& name);
    
    std::string get_symbol() const;
    void set_symbol(const std::string& symbol);
    
    double get_price() const;
    void set_price(double price);

    bool save(Database& db);
    static Crypto find_by_id(Database& db, int crypto_id);
};

/*+++
STOCK MODEL
---*/
class Stock {
private:
    int id;
    int user_id;
    int crypto_id;
    double amount;

public:
    Stock();
    Stock(int id, int user_id, int crypto_id, double amount);

    // Getters and Setters
    int get_id() const;
    void set_id(int id);
    
    int get_user_id() const;
    void set_user_id(int user_id);
    
    int get_crypto_id() const;
    void set_crypto_id(int crypto_id);
    
    double get_amount() const;
    void set_amount(double amount);

    bool save(Database& db);
    static Stock find_by_id(Database& db, int stock_id);
};

/*+++
TRANSACTION MODEL
---*/
class Transaction {
private:
    int id;
    int user_id;
    int crypto_id;
    double amount;
    double price;
    std::string type;
    std::string date;

public:
    Transaction();
    Transaction(int id, int user_id, int crypto_id, double amount, double price, const std::string& type, const std::string& date);
    
    // Getters and Setters
    int get_id() const;
    void set_id(int id);
    
    int get_user_id() const;
    void set_user_id(int user_id);
    
    int get_crypto_id() const;
    void set_crypto_id(int crypto_id);
    
    double get_amount() const;
    void set_amount(double amount);
    
    double get_price() const;
    void set_price(double price);
    
    std::string get_type() const;
    void set_type(const std::string& type);
    
    std::string get_date() const;
    void set_date(const std::string& date);

    bool save(Database& db);
    static Transaction find_by_id(Database& db, int transaction_id);
};

#endif // DATABASE_HH
