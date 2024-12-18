#pragma once
#ifndef CRYPT_HH
#define CRYPT_HH

#include <string>
#include <database.hh>

bool compare_hashed_password(const std::string &password, const std::string &password_hash);

std::string generate_auth_token(const User &user);

#endif // CRYPT_HH