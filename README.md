# System Bank Admin GUI

## Opis Projektu

**System Bank Admin GUI** to panel administracyjny stworzony do wspomagania zarządzania aplikacją System Bank. Panel admina umożliwia łatwą interakcję z systemem bankowym, dostarczając funkcji takich jak zarządzanie pracownikami, przeglądanie wniosków użytkowników, usuwanie pracowników oraz przeglądanie statystyk aplikacji.

## Funkcje

1. **Logowanie Administratora:**
   - Panel administracyjny umożliwia zalogowanie się do systemu za pomocą danych administratora.

2. **Zarządzanie Pracownikami:**
   - Wyświetlanie listy pracowników.
   - Usuwanie pracowników z systemu.

3. **Wnioski o Utworzenie Konta:**
   - Przeglądanie wniosków użytkowników o utworzenie konta.
   - Akceptowanie lub odrzucanie wniosków.

4. **Statystyki Aplikacji:**
   - Przeglądanie statystyk dotyczących działania aplikacji.

5. **Integracja z API:**
   - Projekt wykorzystuje bibliotekę **ApiService** do wymiany danych z API Systemu Bankowego.

## Zdjęcia

1. **Panel Logowania:**
   ![Panel Logowania](/screenshots/login_panel.png)

2. **Lista Pracowników:**
   ![Lista Pracowników](/screenshots/employee_list.png)

3. **Wnioski o Utworzenie Konta:**
   ![Wnioski o Utworzenie Konta](/screenshots/account_requests.png)

4. **Statystyki Aplikacji:**
   ![Statystyki Aplikacji](/screenshots/app_statistics.png)

## Wymagania Systemowe

- Qt Framework
- C++ Compiler
- **ApiService** Library (dostępna w [repozytorium](https://github.com/twojlogin/apiservice))

## Instalacja

1. Sklonuj repozytorium:

   ```bash
   git clone https://github.com/twojlogin/system-bank-admin-gui.git
