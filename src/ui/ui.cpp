/**
 * @file ui.cpp
 * @brief Implementation of user interface utilities.
 */

#include "ui.hpp"
#include <iostream>
#include <limits>

namespace ui {

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void printHeader(const std::string& title) {
    clearScreen();
    std::cout << "========================================" << std::endl;
    std::cout << "          " << title << std::endl;
    std::cout << "========================================" << std::endl;
}

void pauseAndContinue() {
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

} // namespace ui
