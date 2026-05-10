cmake_minimum_required(VERSION 3.14)
project(
    ATM_Project
    VERSION 0.1.0
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

# GoogleTest for unit testing
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
)
# For Windows: prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Source files
file(GLOB_RECURSE ATM_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
list(FILTER ATM_SOURCES EXCLUDE REGEX "src/main.cpp")

add_library(atm_lib STATIC ${ATM_SOURCES})
target_link_libraries(atm_lib PUBLIC sodium nlohmann_json::nlohmann_json)
target_include_directories(atm_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(atm src/main.cpp)
target_link_libraries(atm PRIVATE atm_lib)

# Tests
enable_testing()
add_executable(atm_tests
    tests/test_auth.cpp
    tests/test_models.cpp
    tests/test_logic.cpp
)
target_link_libraries(atm_tests PRIVATE atm_lib GTest::gtest_main)
add_test(NAME ATM_UnitTests COMMAND atm_tests)
