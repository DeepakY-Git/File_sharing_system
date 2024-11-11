cmake_minimum_required(VERSION 3.10)
project(distributed_file_sharing)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

# Find and link necessary libraries
find_package(Poco REQUIRED COMPONENTS Foundation)
find_package(PostgreSQL REQUIRED)

# Manual configuration for libpqxx if find_package doesn't work
find_library(PQXX_LIBRARY NAMES pqxx)
find_path(PQXX_INCLUDE_DIR NAMES pqxx/pqxx)

if(NOT PQXX_LIBRARY OR NOT PQXX_INCLUDE_DIR)
    message(FATAL_ERROR "libpqxx not found. Please install libpqxx-dev package")
endif()

# Include directories
include_directories(
    ${Poco_INCLUDE_DIRS}
    ${PostgreSQL_INCLUDE_DIRS}
    ${PQXX_INCLUDE_DIR}
    include
)

# Add executable target
add_executable(distributed_file_sharing
    src/main.cpp
    src/UserManager.cpp
    src/FileManager.cpp
    src/DatabaseManager.cpp
)

# Link libraries
target_link_libraries(distributed_file_sharing
    PRIVATE
    Poco::Foundation
    ${PQXX_LIBRARY}
    ${PostgreSQL_LIBRARIES}
)

# Print status
message(STATUS "PostgreSQL_LIBRARIES = ${PostgreSQL_LIBRARIES}")
message(STATUS "PQXX_LIBRARY = ${PQXX_LIBRARY}")
message(STATUS "PQXX_INCLUDE_DIR = ${PQXX_INCLUDE_DIR}")