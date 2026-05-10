# ATM System - UML Documentation

This document contains visual representations of the system architecture and logic using Mermaid syntax.

## 1. Use Case Diagram

Describes the interactions between actors (User and Administrator) and the system.

```mermaid
graph LR
    User((Bank User))
    Admin((Administrator))

    subgraph ATM_System [ATM System]
        UC1(Login)
        UC2(Check Balance)
        UC3(Deposit Funds)
        UC4(Withdraw Funds)
        UC5(View History)
        UC6(Logout)
        UC7(Create New Account)
        UC8(Reset User PIN)
        UC9(Unlock Account)
        UC10(List All Accounts)
        UC11(Initial Setup)
    end

    User --- UC1
    UC1 -.-> UC2
    UC1 -.-> UC3
    UC1 -.-> UC4
    UC1 -.-> UC5
    UC1 -.-> UC6

    Admin --- UC1
    UC1 -.-> UC7
    UC1 -.-> UC8
    UC1 -.-> UC9
    UC1 -.-> UC10
    
    Admin --- UC11
```

## 2. Sequence Diagram - Successful Login

```mermaid
sequenceDiagram
    participant U as User/Admin
    participant A as ATMSystem
    participant CR as auth (libsodium)
    participant ST as storage (JSON)

    U->>A: Enter Account Number & PIN
    A->>A: Check if account exists in memory
    A->>CR: verifyPassword(hashedPassword, plainPin)
    CR-->>A: true (Match)
    A->>A: Reset loginAttempts
    A->>A: Log "Login" to user history
    A->>ST: saveState()
    A->>U: Display User/Admin Menu
```

## 3. Sequence Diagram - Account Lockout

```mermaid
sequenceDiagram
    participant U as User
    participant A as ATMSystem
    participant CR as auth (libsodium)

    U->>A: Enter Wrong PIN (3rd attempt)
    A->>CR: verifyPassword(...)
    CR-->>A: false (No match)
    A->>A: Increment loginAttempts
    Note over A: loginAttempts >= 3
    A->>A: Set isBlocked = true
    A->>U: Display "ACCOUNT BLOCKED" error
```

## 4. Class Diagram (Simplified)

*Note: For detailed, interactive class diagrams generated from code, see the "Classes" section in Doxygen.*

```mermaid
classDiagram
    class ATMSystem {
        -map users
        -string dataFile
        +run()
        -adminMenu()
        -userMenu()
    }

    class User {
        +string accountNumber
        +double balance
        +bool isBlocked
        +vector history
    }

    class Transaction {
        +string type
        +double amount
    }

    ATMSystem "1" *-- "many" User : manages
    User "1" *-- "many" Transaction : contains
```
