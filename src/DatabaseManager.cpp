// DatabaseManager.cpp
#include "DatabaseManager.h"

DatabaseManager::DatabaseManager(const std::string& connectionString)
    : m_connectionString(connectionString) {
    m_connection = std::make_unique<pqxx::connection>(connectionString);
}

pqxx::connection& DatabaseManager::getConnection() {
    return *m_connection;
}