cmake_minimum_required(VERSION 3.15)
project(WebSocketClient)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic")

# Paths to include
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(/usr/local/include) # WebSocket++ & Boost (if from vcpkg)

# Sources
set(SOURCES
    src/WebSocketClient.cpp
    src/UTF8Converter.cpp
)

# Build DLL
add_library(WebSocketClient SHARED ${SOURCES})

# Linking with Boost
target_link_libraries(WebSocketClient boost_system)