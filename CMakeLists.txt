cmake_minimum_required(VERSION 3.15)
project(WebSocketClient)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "/W4 /MT") # Enable all warnings and use static runtime

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${VCPKG_ROOT}/installed/x64-windows/include) # Adjust if using vcpkg

# Link directories (Boost and other dependencies)
link_directories(${VCPKG_ROOT}/installed/x64-windows/lib)

# Source files
set(SOURCES
    src/WebSocketClient.cpp
    src/UTF8Converter.cpp
)

# Build the DLL
add_library(WebSocketClient SHARED ${SOURCES})

# Link Boost libraries
target_link_libraries(WebSocketClient
    ws2_32 # Windows Sockets library
    boost_system # Boost system library
)