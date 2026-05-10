#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <vector>

// Prosta struktura do logowania historii [cite: 13, 33]
struct Transaction {
	std::string type;
	double amount;
};

// Klasa reprezentująca Użytkownika [cite: 6, 8]
class User {
  private:
	std::string accountNumber;		  // [cite: 9]
	size_t pinHash;					  // Zaszyfrowany/hashowany PIN
	double balance;					  // [cite: 12]
	int loginAttempts;				  // [cite: 15]
	bool isBlocked;					  // [cite: 15]
	std::vector<Transaction> history; // [cite: 13]

	// Prosta funkcja haszująca dla demonstracji [cite: 35]
	size_t hashPin(const std::string &pin) const { return std::hash<std::string>{}(pin); }

  public:
	User(std::string acc, std::string pin, double initialBalance)
		: accountNumber(acc), balance(initialBalance), loginAttempts(0), isBlocked(false) {
		pinHash = hashPin(pin);
	}

	bool authenticate(const std::string &pin) {
		if (isBlocked)
			return false;

		if (hashPin(pin) == pinHash) {
			loginAttempts = 0;
			return true;
		} else {
			loginAttempts++;
			if (loginAttempts >= 3) {
				isBlocked = true; // Blokada po 3 próbach
			}
			return false;
		}
	}

	void deposit(double amount) { // [cite: 19]
		balance += amount;
		history.push_back({"Wplata", amount});
	}

	bool withdraw(double amount) { // [cite: 20]
		if (amount > balance)
			return false; // Brak środków [cite: 23]
		balance -= amount;
		history.push_back({"Wyplata", amount});
		return true;
	}

	void addLoginHistory() { history.push_back({"Logowanie", 0}); }
	double getBalance() const { return balance; } // [cite: 19]
	bool getIsBlocked() const { return isBlocked; }
	std::string getAccountNumber() const { return accountNumber; }

	void showHistory() const { // [cite: 24]
		std::cout << "\n--- Historia Operacji ---" << std::endl;
		for (const auto &t : history) {
			std::cout << t.type << ": " << (t.amount > 0 ? std::to_string(t.amount) : "")
					  << std::endl;
		}
	}

	void resetPin(const std::string &newPin) { // Opcja administratora [cite: 27]
		pinHash = hashPin(newPin);
		isBlocked = false;
		loginAttempts = 0;
	}
};

// Główna klasa Systemu Bankowego
class ATMSystem {
  private:
	std::map<std::string, User> users;

  public:
	void addUser(const User &user) { users.insert({user.getAccountNumber(), user}); }

	void run() {
		while (true) {
			std::string acc, pin;
			std::cout << "\n=== BANKOMAT ===\nNumer konta: ";
			std::cin >> acc;
			std::cout << "PIN: ";
			std::cin >> pin;

			if (users.find(acc) != users.end()) {
				User &currentUser = users.at(acc);

				if (currentUser.authenticate(pin)) {
					currentUser.addLoginHistory();
					userMenu(currentUser);
				} else if (currentUser.getIsBlocked()) {
					std::cout << "Konto zablokowane! Skontaktuj sie z administratorem.\n";
				} else {
					std::cout << "Bledny PIN.\n";
				}
			} else {
				std::cout << "Nie znaleziono uzytkownika.\n";
			}
		}
	}

	void userMenu(User &user) {
		int choice;
		do {
			std::cout << "\n1. Saldo\n2. Wplata\n3. Wyplata\n4. Historia\n5. Wyloguj\nWybor: ";
			std::cin >> choice;

			switch (choice) {
			case 1:
				std::cout << "Saldo: " << std::fixed << std::setprecision(2) << user.getBalance()
						  << " PLN\n";
				break;
			case 2: {
				double amt;
				std::cout << "Kwota wplaty: ";
				std::cin >> amt;
				user.deposit(amt);
				break;
			}
			case 3: {
				double amt;
				std::cout << "Kwota wyplaty: ";
				std::cin >> amt;
				if (user.withdraw(amt))
					std::cout << "Wyplacono.\n";
				else
					std::cout << "Brak srodkow na koncie!\n";
				break;
			}
			case 4:
				user.showHistory();
				break;
			}
		} while (choice != 5); // Wylogowanie [cite: 24]
	}
};

int main() {
	ATMSystem atm;

	// Scenariusz testowy: Tworzenie konta [cite: 26, 44]
	atm.addUser(User("123", "1111", 1000.0));
	atm.addUser(User("456", "2222", 500.0));

	atm.run();
	return 0;
}
