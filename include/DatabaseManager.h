// DatabaseManager.h
#pragma once

#include <string>
#include <pqxx/pqxx>

class DatabaseManager {
public:
    DatabaseManager(const std::string& connectionString);
    pqxx::connection& getConnection();

private:
    std::string m_connectionString;
    std::unique_ptr<pqxx::connection> m_connection;
};