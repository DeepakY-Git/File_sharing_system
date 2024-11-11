#include "UserManager.h"
#include "FileManager.h"
#include "DatabaseManager.h"
#include <iostream>
#include <limits>
#include <thread>
#include <chrono>

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void displayLogo() {
    clearScreen();
    std::cout << R"(
    ███████╗██╗██╗     ███████╗    ███████╗██╗  ██╗ █████╗ ██████╗ ███████╗
    ██╔════╝██║██║     ██╔════╝    ██╔════╝██║  ██║██╔══██╗██╔══██╗██╔════╝
    █████╗  ██║██║     █████╗      ███████╗███████║███████║██████╔╝█████╗  
    ██╔══╝  ██║██║     ██╔══╝      ╚════██║██╔══██║██╔══██║██╔══██╗██╔══╝  
    ██║     ██║███████╗███████╗    ███████║██║  ██║██║  ██║██║  ██║███████╗
    ╚═╝     ╚═╝╚══════╝╚══════╝    ╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝
    )" << std::endl;
    std::cout << "                     Secure File Sharing System v1.0\n";
    std::cout << "================================================================\n\n";
}

void waitForEnter() {
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void displayProgressBar(const std::string& message) {
    std::cout << message;
    std::cout.flush();
    for (int i = 0; i < 20; i++) {
        std::cout << "█";
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    std::cout << " Done!" << std::endl;
}

void displayMenu() {
    std::cout << "\nMain Menu:\n";
    std::cout << "1. Upload File\n";
    std::cout << "2. Download File\n";
    std::cout << "3. Generate Shareable Link\n";
    std::cout << "4. Help\n";
    std::cout << "5. Exit\n";
    std::cout << "\nEnter your choice (1-5): ";
}

void displayHelp() {
    clearScreen();
    std::cout << "\nHelp Guide:\n";
    std::cout << "============\n\n";
    std::cout << "1. Upload File:\n";
    std::cout << "   - Enter the complete file path\n";
    std::cout << "   - Supported file types: All\n\n";
    std::cout << "2. Download File:\n";
    std::cout << "   - Enter the file ID provided during upload\n";
    std::cout << "   - Files are downloaded to the default directory\n\n";
    std::cout << "3. Generate Shareable Link:\n";
    std::cout << "   - Enter file ID to generate a shareable link\n";
    std::cout << "   - Links expire after 24 hours\n\n";
    waitForEnter();
}

bool handleSignup(UserManager& userManager, const std::string& username) {
    std::string password, confirmPassword;
    
    clearScreen();
    displayLogo();
    std::cout << "New User Registration\n";
    std::cout << "====================\n\n";
    std::cout << "Username: " << username << "\n";
    
    do {
        std::cout << "Enter password: ";
        std::cin >> password;
        std::cout << "Confirm password: ";
        std::cin >> confirmPassword;
        
        if (password != confirmPassword) {
            std::cout << "\nPasswords do not match! Please try again.\n\n";
        }
    } while (password != confirmPassword);
    
    displayProgressBar("Creating new account... ");
    
    if (userManager.registerUser(username, password)) {
        std::cout << "\nAccount created successfully!";
        waitForEnter();
        return true;
    } else {
        std::cout << "\nFailed to create account. Please try again later.";
        waitForEnter();
        return false;
    }
}

bool handleLogin(UserManager& userManager, std::string& loggedInUsername) {
    std::string username, password;
    int attempts = 3;
    char choice;

    while (attempts > 0) {
        clearScreen();
        displayLogo();
        std::cout << "Login (" << attempts << " attempts remaining)\n";
        std::cout << "Username: ";
        std::cin >> username;
        
        if (!userManager.userExists(username)) {
            std::cout << "\nUsername doesn't exist!\n";
            std::cout << "Would you like to create a new account? (y/n): ";
            std::cin >> choice;
            
            if (tolower(choice) == 'y') {
                if (handleSignup(userManager, username)) {
                    loggedInUsername = username;
                    return true;
                }
                return false;
            } else {
                attempts--;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                continue;
            }
        }

        std::cout << "Password: ";
        std::cin >> password;

        if (userManager.authenticateUser(username, password)) {
            displayProgressBar("Logging in... ");
            loggedInUsername = username;
            return true;
        }

        attempts--;
        if (attempts > 0) {
            std::cout << "\nInvalid credentials. Please try again.\n";
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    }

    std::cout << "\nToo many failed attempts. Please try again later.";
    waitForEnter();
    return false;
}

int main() {
    try {
        std::string connectionString = "host=127.0.1.1 port=5433 dbname=file_sharing user=yugabyte password=yugabyte";
        DatabaseManager dbManager(connectionString);
        UserManager userManager(dbManager.getConnection());
        FileManager fileManager(dbManager.getConnection());

        displayLogo();
        std::this_thread::sleep_for(std::chrono::seconds(2));

        std::string loggedInUsername;
        if (!handleLogin(userManager, loggedInUsername)) {
            return 1;
        }

        bool running = true;
        while (running) {
            clearScreen();
            displayLogo();
            std::cout << "Logged in as: " << loggedInUsername << std::endl;
            displayMenu();

            int choice;
            std::cin >> choice;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            switch (choice) {
                case 1: { // Upload File
                    std::string filePath;
                    std::cout << "Enter file path to upload: ";
                    std::getline(std::cin, filePath);
                    
                    displayProgressBar("Uploading file... ");
                    std::string out = fileManager.uploadFile(loggedInUsername, filePath);
                    
                    if (out!="") {
                        std::cout << "\nFile uploaded successfully!";
                        std::cout << "\nFile ID : " << out;
                    } else {
                        std::cout << "\nFile upload failed.";
                    }
                    waitForEnter();
                    break;
                }
                case 2: { // Download File
                    std::string fileId;
                    std::cout << "Enter file ID to download: ";
                    std::cin >> fileId;
                    std::string destinationPath = "/var/www/html/files/";
                    
                    displayProgressBar("Downloading file... ");
                    
                    if (fileManager.downloadFile(loggedInUsername, fileId, destinationPath)) {
                        std::cout << "\nFile downloaded successfully to: " << destinationPath;
                    } else {
                        std::cout << "\nFile download failed.";
                    }
                    waitForEnter();
                    break;
                }
                case 3: { // Generate Link
                    std::string fileId;
                    std::cout << "Enter file ID to generate shareable link: ";
                    std::cin >> fileId;
                    
                    displayProgressBar("Generating link... ");
                    
                    std::string shareableLink = fileManager.generateShareableLink(fileId);
                    std::cout << "\nShareable link: " << shareableLink;
                    waitForEnter();
                    break;
                }
                case 4: // Help
                    displayHelp();
                    break;
                case 5: { // Exit
                    std::cout << "Logging out " << loggedInUsername << "...\n";
                    displayProgressBar("Saving session data... ");
                    std::cout << "\nThank you for using File Share! Goodbye!";
                    waitForEnter();
                    running = false;
                    break;
                }
                default:
                    std::cout << "\nInvalid choice. Please try again.";
                    waitForEnter();
                    break;
            }
        }

        return 0;
    } catch (const std::exception& e) {
        std::cerr << "\nError: " << e.what();
        waitForEnter();
        return 1;
    }
}