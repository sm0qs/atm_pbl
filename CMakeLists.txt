cmake_minimum_required(VERSION 4.3)
project(
    ATM_Project
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Dependencies
include(FetchContent)

# libsodium for secure hashing
FetchContent_Declare(
    sodium
    GIT_REPOSITORY https://github.com/robinlinden/libsodium-cmake.git
    GIT_TAG efe978b574516d7708c0feeb5231cf7ab4906283
)
FetchContent_MakeAvailable(sodium)

# nlohmann_json for data storage
FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.12.0
)
FetchContent_MakeAvailable(json)

# Source files
file(GLOB_RECURSE ATM_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_executable(atm ${ATM_SOURCES})
target_link_libraries(atm PRIVATE sodium nlohmann_json::nlohmann_json)

# Include directories
target_include_directories(atm PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
