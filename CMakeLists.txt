cmake_minimum_required(VERSION 4.3)
project(
	ATM_Project
	VERSION 1.0
	LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(atm src/main.cpp)
