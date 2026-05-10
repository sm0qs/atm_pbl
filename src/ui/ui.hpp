/**
 * @file ui.hpp
 * @brief User interface components and utilities.
 */

#ifndef ATM_UI_HPP
#define ATM_UI_HPP

#include <string>

/**
 * @namespace ui
 * @brief Handles console output and input formatting.
 */
namespace ui {

/**
 * @brief Clears the console window.
 */
void clearScreen();

/**
 * @brief Prints a formatted header with a title.
 * @param title Title to display.
 */
void printHeader(const std::string& title);

/**
 * @brief Prompts the user to press enter to continue.
 */
void pauseAndContinue();

} // namespace ui

#endif
