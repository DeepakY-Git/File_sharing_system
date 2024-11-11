// UserManager.cpp
#include "UserManager.h"
#include <Poco/SHA1Engine.h>
#include <Poco/DigestStream.h>
#include <iostream>

UserManager::UserManager(pqxx::connection& connection) : m_connection(connection) {}

bool UserManager::registerUser(const std::string& username, const std::string& password) {
    try {
        // Hash the password
        Poco::SHA1Engine sha1;
        Poco::DigestOutputStream dos(sha1);
        dos << password;
        dos.close();
        std::string hashedPassword = Poco::DigestEngine::digestToHex(sha1.digest());

        // Create a transaction
        pqxx::work txn(m_connection);

        // Insert the user
        txn.exec_params(
            "INSERT INTO users (username, password) VALUES ($1, $2)",
            username,
            hashedPassword
        );

        // Commit the transaction
        txn.commit();
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error registering user: " << e.what() << std::endl;
        return false;
    }
}

bool UserManager::authenticateUser(const std::string& username, const std::string& password) {
    try {
        // Hash the provided password
        Poco::SHA1Engine sha1;
        Poco::DigestOutputStream dos(sha1);
        dos << password;
        dos.close();
        std::string hashedPassword = Poco::DigestEngine::digestToHex(sha1.digest());

        // Create a transaction
        pqxx::work txn(m_connection);

        // Query the database
        pqxx::result result = txn.exec_params(
            "SELECT password FROM users WHERE username = $1",
            username
        );

        if (result.empty()) {
            return false;
        }

        std::string storedPassword = result[0][0].as<std::string>();
        return storedPassword == hashedPassword;
    } catch (const std::exception& e) {
        std::cerr << "Error authenticating user: " << e.what() << std::endl;
        return false;
    }
}

bool UserManager::userExists(const std::string& username) {
    try {
        pqxx::work txn(m_connection);

        // Query the database to check if the user exists
        pqxx::result result = txn.exec_params(
            "SELECT 1 FROM users WHERE username = $1 LIMIT 1",
            username
        );

        // Check if any results were returned
        return !result.empty();
    } catch (const std::exception& e) {
        std::cerr << "Error checking if user exists: " << e.what() << std::endl;
        return false;
    }
}
