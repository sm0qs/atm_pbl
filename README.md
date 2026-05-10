# Secure ATM Simulator (C++)

Zaawansowany symulator bankomatu stworzony w języku C++, wykorzystujący nowoczesne standardy kryptograficzne oraz zautomatyzowany system budowania projektu. Aplikacja realizuje wszystkie wymagania zawarte w specyfikacji technicznej projektu Bankomat.

## Bezpieczeństwo i Technologia

Projekt został zaimplementowany z naciskiem na bezpieczeństwo oraz modularność:
* **Kryptografia (libsodium):** PIN-y użytkowników są zabezpieczone algorytmem Argon2id (funkcja `crypto_pwhash`). Zgodnie z wymaganiami bezpieczeństwa, system nie przechowuje haseł w postaci jawnej.
* **Trwałość danych (JSON):** Stan kont oraz historia operacji są zapisywane w formacie JSON, co zapewnia trwałość danych między sesjami programu.
* **Automatyzacja (CMake):** Zastosowanie modułu FetchContent w pliku CMakeLists.txt sprawia, że biblioteki zewnętrzne (libsodium oraz nlohmann_json) są pobierane i konfigurowane automatycznie podczas budowania projektu.

## Funkcjonalności

### Użytkownik
* **Logowanie:** Proces autoryzacji z mechanizmem blokady konta po trzech nieudanych próbach.
* **Zarządzanie środkami:** Sprawdzanie aktualnego salda, wpłaty oraz wypłaty z obowiązkową weryfikacją dostępnych funduszy.
* **Historia:** Wgląd w listę operacji, takich jak wpłaty, wypłaty i sesje logowania.

### Administrator
* Tworzenie nowych kont użytkowników.
* Resetowanie kodów PIN.
* Odblokowywanie kont zablokowanych przez system.

## Struktura Projektu

Kod jest podzielony na dedykowane przestrzenie nazw, co zapewnia wysoką modularność:
* **auth:** Obsługa bezpiecznego hashowania i weryfikacji kodów PIN.
* **logic:** Główna logika sterująca systemem ATM.
* **storage:** Warstwa trwałego przechowywania danych i serializacji do formatu JSON.
* **ui:** Obsługa interfejsu użytkownika oraz walidacja danych wejściowych.

## Kompilacja i Uruchomienie

Projekt wykorzystuje system budowania CMake.

1. **Konfiguracja i kompilacja:**
   ```bash
   mkdir build && cd build
   cmake ..
   make
