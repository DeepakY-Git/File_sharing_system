// FileManager.cpp
#include "FileManager.h"
#include <Poco/File.h>
#include <Poco/Path.h>
#include <Poco/UUID.h>
#include <Poco/UUIDGenerator.h>
#include <fstream>
#include <iostream>
#include <filesystem>

FileManager::FileManager(pqxx::connection& connection) : m_connection(connection) {}

std::string FileManager::uploadFile(const std::string& username, const std::string& filePath) {
    try {
        Poco::File file(filePath);
        if (!file.exists() || !file.isFile()) {
            std::cerr << "File does not exist or is not a regular file." << std::endl;
            return "";
        }

        // Read file content in binary mode
        std::ifstream ifs(filePath, std::ios::binary);
        std::vector<char> content((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
        ifs.close();

        // Generate UUID for file
        Poco::UUID uuid = Poco::UUIDGenerator::defaultGenerator().create();
        std::string fileId = uuid.toString();

        // Create a transaction
        pqxx::work txn(m_connection);

        // Insert the file content as binary data (BLOB)
        txn.exec_params(
            "INSERT INTO files (file_id, username, file_path, content) VALUES ($1, $2, $3, $4)",
            fileId,
            username,
            filePath,
            pqxx::binarystring(content.data(), content.size()) // Store as binary
        );

        // Commit the transaction
        txn.commit();
        return fileId;
    } catch (const std::exception& e) {
        std::cerr << "Error uploading file: " << e.what() << std::endl;
        return "";
    }
}

bool FileManager::downloadFile(const std::string& username, const std::string& fileId, const std::string& destinationPath) {
    try {
        // Create a transaction
        pqxx::work txn(m_connection);

        // Query the database
        pqxx::result result = txn.exec_params(
            "SELECT content, file_path FROM files WHERE file_id = $1 AND username = $2",
            fileId,
            username
        );

        if (result.empty()) {
            std::cerr << "File not found or access denied." << std::endl;
            return false;
        }

        // Retrieve binary data as a vector of bytes
        pqxx::binarystring binaryContent(result[0][0]);
        std::vector<char> content(binaryContent.data(), binaryContent.data() + binaryContent.size());

        // Determine the destination path with file extension
        std::string filePathExtension = std::filesystem::path(result[0][1].as<std::string>()).extension().string();
        std::ofstream ofs(destinationPath + fileId + filePathExtension, std::ios::binary);

        if (!ofs) {
            std::cerr << "Error: Could not create file at " << destinationPath << std::endl;
            return false;
        }

        // Write the binary data to the file
        ofs.write(content.data(), content.size());
        ofs.close();
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error downloading file: " << e.what() << std::endl;
        return false;
    }
}

std::string FileManager::generateShareableLink(const std::string& fileId) {
    pqxx::work txn(m_connection);

        // Query the database
        pqxx::result result = txn.exec_params(
            "SELECT file_path FROM files WHERE file_id = $1",
            fileId
        );

        if (result.empty()) {
            std::cerr << "File not found or access denied." << std::endl;
            return "";
        }
        std::string filePathExtension = std::filesystem::path(result[0][0].as<std::string>()).extension().string();
    return "http://localhost/files/" + fileId + filePathExtension;
}
