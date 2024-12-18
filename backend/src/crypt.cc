#include <string>
#include <crypt.hh>
#include <database.hh>

std::string hash_password(const std::string &password) {
    return password;
}

bool compare_hashed_password(const std::string &password, const std::string &password_hash) {
    return password_hash == hash_password(password);
}

std::string generate_auth_token(const User &user) {
    std::string user_data = std::to_string(user.get_id()) + user.get_email();
    return hash_password(user_data);
}