# Minimum version and project settings
cmake_minimum_required(VERSION 3.10)
project(CPPBackendServer)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 17)

# Add source files
add_executable(cpp-backend-server
    src/main.cc
    src/server.cc
    src/http.cc
    src/models.cc
    src/database.cc
)

# Include directories
target_include_directories(cpp-backend-server PRIVATE inc)

# Link Winsock2 for networking (Windows only)
if (WIN32)
    target_link_libraries(cpp-backend-server ws2_32)
endif()

# Set ATRC library directories
if (WIN32)
    set(ATRC_DIR "${PROJECT_SOURCE_DIR}/ATRC/libs/win")
elseif (UNIX)
    set(ATRC_DIR "${PROJECT_SOURCE_DIR}/ATRC/libs/linux")
endif()

# Find and link ATRC library
find_library(ATRC NAMES ATRC REQUIRED PATHS ${ATRC_DIR})
include_directories("${PROJECT_SOURCE_DIR}/atrc/include")
target_link_libraries(cpp-backend-server ${ATRC})

# SQLite integration
if (WIN32)
    # Path to SQLite files
    set(SQLITE_DIR "${PROJECT_SOURCE_DIR}/libs/")
    find_library(SQLITE3 NAMES sqlite3 REQUIRED PATHS ${SQLITE_DIR})
    
    # Include SQLite headers
    include_directories(cpp-backend-server ${SQLITE_DIR})
    
    # Link SQLite library
    target_link_libraries(cpp-backend-server ${SQLITE3})
endif()
