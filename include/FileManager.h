// FileManager.h
#pragma once

#include <string>
#include <pqxx/pqxx>

class FileManager {
public:
    FileManager(pqxx::connection& connection);
    std::string uploadFile(const std::string& username, const std::string& filePath);
    bool downloadFile(const std::string& username, const std::string& fileId, const std::string& destinationPath);
    std::string generateShareableLink(const std::string& fileId);

private:
    pqxx::connection& m_connection;
};