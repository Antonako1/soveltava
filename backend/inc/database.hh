#pragma once
#ifndef DATABASE_HH
#define DATABASE_HH

#include <sqlite3.h>
#include <iostream>
#include <string>
#include <vector>
#include <json.hpp> 
using json = nlohmann::json;

class Database {
protected:
    sqlite3* db;

public:
    std::string db_name;
    Database();
    
    Database(const std::string& db_name);

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

extern Database db; /*main.cc*/

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

    static User find_by_email(Database& db, const std::string& email);

    json to_json();    
};

/*+++
CRYPTO MODEL
---*/
class Crypto {
private:
    int id;
    std::string tag;
    std::string name;
    double price;

public:
    Crypto();
    Crypto(int id, const std::string& name, const std::string& tag, double price);
    
    // Getters and Setters
    int get_id() const;
    void set_id(int id);
    
    std::string get_name() const;
    void set_name(const std::string& name);
    
    std::string get_tag() const;
    void set_tag(const std::string& tag);
    
    double get_price() const;
    void set_price(double price);

    bool save(Database& db);
    static Crypto find_by_id(Database& db, int crypto_id);

    static Crypto find_by_tag(Database& db, const std::string& tag);

    json to_json();  
};

/*+++
STOCK MODEL
---*/
class Stock {
private:
    int id;
    std::string tag;
    std::string name;
    double price;

public:
    Stock();
    Stock(int id, const std::string& tag, const std::string& name, double price);

    // Getters and Setters
    int get_id() const;
    void set_id(int id);
    
    std::string get_tag() const;
    void set_tag(const std::string& tag);
    
    std::string get_name() const;
    void set_name(const std::string& name);
    
    double get_price() const;
    void set_price(double price);

    bool save(Database& db);
    static Stock find_by_id(Database& db, int stock_id);

    static Stock find_by_tag(Database& db, const std::string& tag);

    json to_json();  
};

/*+++
TRANSACTION MODEL
---*/
class Transaction {
private:
    int id;
    int user_id;
    int crypto_id;
    int stock_id;
    double amount;
    double price;
    std::string type;
    std::string date;

public:
    Transaction();
    Transaction(int id, int user_id, int crypto_id, int stock_id, double amount, double price, const std::string& type, const std::string& date);
    
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

    int get_stock_id() const;
    void set_stock_id(int stock_id);
    
    std::string get_type() const;
    void set_type(const std::string& type);
    
    std::string get_date() const;
    void set_date(const std::string& date);

    bool save(Database& db);
    static Transaction find_by_id(Database& db, int transaction_id);

    static Transaction find_by_user_id(Database& db, int user_id);
    static Transaction find_by_crypto_id(Database& db, int crypto_id);
    static Transaction find_by_stock_id(Database& db, int stock_id);



    json to_json();
};

#endif // DATABASE_HH
