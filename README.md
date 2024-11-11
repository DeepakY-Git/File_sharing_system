# Distributed File Sharing System
A distributed file sharing system implemented in C++ using Poco libraries and Yugabyte as the storage backend.

## Overview
The Secure File Sharing System is a command-line application that allows users to:
- Register and authenticate users
- Upload files securely
- Download files
- Generate shareable links for files
- Store files with proper access control

## Prerequisites
Before setting up the project, ensure you have the following installed on your system:

### Required Packages
1. C++ Compiler (GCC/G++)
```bash
sudo apt update
sudo apt install build-essential
```

2. CMake (Build System)
```bash
sudo apt install cmake
```

3. Poco Libraries
```bash
sudo apt install libpoco-dev
```

4. PostgreSQL and libpqxx (C++ PostgreSQL Client)
```bash
sudo apt install postgresql libpqxx-dev
```

5. YugabyteDB
Follow these steps to install YugabyteDB:
```bash
# Download YugabyteDB
wget https://downloads.yugabyte.com/releases/latest/yugabyte-2.23.0.0-linux-x86_64.tar.gz

# Extract the package
tar xvf yugabyte-2.23.0.0-linux-x86_64.tar.gz

# Navigate to YugabyteDB directory
cd yugabyte-2..0.0/
```

## Project Setup

### 1. Clone the Repository
```bash
git clone <repository-url>
cd my_project
```

### 2. Project Structure
The project follows this structure:
```
my_project/
├── CMakeLists.txt
├── include/
│   ├── DatabaseManager.h
│   ├── FileManager.h
│   └── UserManager.h
├── src/
│   ├── DatabaseManager.cpp
│   ├── FileManager.cpp
│   ├── UserManager.cpp
│   └── main.cpp
└── logs
```

### 3. Database Setup

1. Start YugabyteDB cluster:
```bash
./bin/yugabyted start
```

2. Connect to YugabyteDB:
```bash
./bin/ysqlsh -h 127.0.1.1 -p 5433 -U yugabyte
```

3. Create necessary database and tables:
```sql
CREATE DATABASE file_sharing;
\c file_sharing

CREATE TABLE users (
    username VARCHAR PRIMARY KEY,
    password VARCHAR NOT NULL
);

CREATE TABLE files (
    file_id VARCHAR PRIMARY KEY,
    username VARCHAR REFERENCES users(username),
    file_path VARCHAR NOT NULL,
    content BYTEA NOT NULL
);
```

### 4. Build the Project

1. Create and navigate to build directory:
```bash
mkdir build
cd build
```

2. Generate build files:
```bash
cmake ..
```

3. Build the project:
```bash
make
```

## Running the Application

1. Ensure YugabyteDB is running:
```bash
./bin/yugabyted status
```

2. Create the files directory for downloads:
```bash
sudo mkdir -p /var/www/html/files
sudo chmod 777 /var/www/html/files
```

3. Run the application:
```bash
./distributed_file_sharing
```

## Usage Guide

### 1. User Registration and Login
- When you start the application, you'll be prompted to log in
- If you're a new user, you can create an account when prompted
- You have 3 login attempts before the system locks you out

### 2. Main Menu Options
After logging in, you'll see these options:
1. Upload File
2. Download File
3. Generate Shareable Link
4. Help
5. Exit

### 3. File Operations

#### Uploading Files
1. Select option 1
2. Enter the complete file path
3. The system will return a File ID - save this for future reference

#### Downloading Files
1. Select option 2
2. Enter the File ID
3. Files are downloaded to `/var/www/html/files/`

#### Generating Shareable Links
1. Select option 3
2. Enter the File ID
3. The system will generate a shareable link

## Security Features
- Password hashing using SHA1
- Secure binary file storage in database
- User authentication required for file operations
- UUID-based file identification

## Common Issues and Troubleshooting

### Database Connection Issues
If you can't connect to the database, verify:
1. YugabyteDB is running: `./bin/yugabyted status`
2. Correct connection string in main.cpp (default: "host=127.0.1.1 port=5433 dbname=file_sharing user=yugabyte password=yugabyte")

### File Permission Issues
If you encounter file access errors:
1. Verify the /var/www/html/files directory exists and has proper permissions
2. Ensure you have read/write permissions for the files you're trying to upload

## Limitations
- File sharing links expire after 24 hours
- System requires local file access for uploads
- Currently supports single-node deployment only

## System Requirements
- Linux-based operating system
- Minimum 1GB RAM
- 500MB free disk space
- Internet connection for database operations


