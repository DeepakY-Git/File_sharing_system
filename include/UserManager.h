// UserManager.h
#pragma once

#include <string>
#include <pqxx/pqxx>

class UserManager {
public:
    UserManager(pqxx::connection& connection);
    bool registerUser(const std::string& username, const std::string& password);
    bool authenticateUser(const std::string& username, const std::string& password);
    bool userExists(const std::string& username);

private:
    pqxx::connection& m_connection;
};