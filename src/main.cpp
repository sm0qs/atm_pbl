/**
 * @file main.cpp
 * @brief Entry point for the ATM project.
 */

#include <iostream>
#include <limits>

/**
 * @brief Clears the console screen.
 *
 * Uses a platform-specific system command to clear the terminal output:
 * - On Windows the `cls` command is used.
 * - On POSIX systems the `clear` command is used.
 */
void clearScreen() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

/**
 * @brief Reads a value of type T from the user with a prompt.
 *
 * Prints @p prompt to standard output and attempts to parse a value of type
 * `T` from `std::cin`. On parse failure the stream is cleared and the rest
 * of the input line is discarded.
 *
 * Example: `int choice; readValue<int>(choice, "Enter choice: ");`
 *
 * @tparam T The type of value to read (e.g. `int`, `double`).
 * @param[out] value Reference where the parsed value will be stored on success.
 * @param[in] prompt The message displayed to the user before reading input.
 * @return `true` if a value of type `T` was successfully read and stored,
 *         `false` if input parsing failed.
 */
template <typename T> bool readValue(T &value, const std::string &prompt) {
	std::cout << prompt;
	if (!(std::cin >> value)) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return false;
	}
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return true;
}

/**
 * @brief Displays the main menu and gets the user's choice.
 * @return The user's menu choice.
 * @retval 1 User Login selected.
 * @retval 2 Admin Login selected.
 * @retval 3 Exit selected.
 */
int menu() {
	clearScreen();
	std::cout << "=== ATM Terminal ===" << std::endl;
	std::cout << "1. User Login" << std::endl;
	std::cout << "2. Admin Login" << std::endl;
	std::cout << "3. Exit" << std::endl;

	int choice;
	while (true) {
		if (readValue<int>(choice, "Enter your choice (1-3): ")) {
			if (choice >= 1 && choice <= 3)
				break;
		}
		std::cout << "Invalid choice. Please enter a number between 1 and 3." << std::endl;
	}
	clearScreen();
	return choice;
}

/**
 * @brief Program entry point.
 * @return Program exit status. Returns 0 on normal termination.
 */
int main() {

	switch (menu()) {
	case 1: {
		std::cout << "User Login selected." << std::endl;
		break;
	}
	case 2: {
		std::cout << "Admin Login selected." << std::endl;
		break;
	}
	case 3: {
		std::cout << "Exiting the program. Goodbye!" << std::endl;
	}
	}

	return 0;
}
