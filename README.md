# Secure ATM Simulator (C++)

An advanced ATM simulator developed in C++, utilizing modern cryptographic standards and an automated project build system. The application fulfills all requirements specified in the "Bankomat.pdf" technical documentation.

## Security and Technology

The project has been implemented with a strong emphasis on security and modularity:
* **Cryptography (libsodium):** User PINs are secured using the Argon2id algorithm (`crypto_pwhash` function). In accordance with security requirements, the system does not store passwords in plain text.
* **Data Persistence (JSON):** Account states and transaction histories are saved in JSON format, ensuring data persistence between program sessions.
* **Automation (CMake):** The use of the FetchContent module in the CMakeLists.txt file ensures that external libraries (libsodium and nlohmann_json) are automatically downloaded and configured during the build process.

## Features

### User
* **Login:** Authentication process with a lockout mechanism after three failed attempts.
* **Fund Management:** Checking current balance, deposits, and withdrawals with mandatory verification of available funds.
* **History:** Access to a list of operations, including deposits, withdrawals, and login sessions.

### Administrator
* Creation of new user accounts.
* Resetting user PINs.
* Unlocking accounts blocked by the system.

## Project Structure

The code is divided into dedicated namespaces, ensuring high modularity:
* **auth:** Handles secure hashing and PIN verification.
* **logic:** Main logic controlling the ATM system.
* **storage:** Data persistence layer and JSON serialization.
* **ui:** User interface handling and input validation.

## Compilation and Execution

The project utilizes the CMake build system.

1. **Configuration and compilation:**
   ```bash
   mkdir build && cd build
   cmake ..
   make
