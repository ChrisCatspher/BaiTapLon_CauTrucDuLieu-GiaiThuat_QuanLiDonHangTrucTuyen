
#include <iostream>
#include <string>

#include "OrderManager.h"
#include "InputUtils.h"

using namespace std;

// ===== MENU =====

void displayMainMenu();

// ===== MAIN =====

int main() {
    OrderManager manager;

    int choice;

    do {
        displayMainMenu();

        // Input user choice

        switch (choice) {
            case 1:
                // Order CRUD - Member 2
                break;

            case 2:
                // Order Processing - Member 3
                break;

            case 3:
                // Order Search - Member 4
                break;

            case 4:
                // Order Statistics - Member 5
                break;

            case 0:
                // Exit program
                break;

            default:
                // Invalid choice
                break;
        }

    } while (choice != 0);

    return 0;
}

// ===== MAIN MENU =====

void displayMainMenu() {
    cout << "\n";
    cout << "====================================\n";
    cout << "     LOGISTICS ORDER MANAGEMENT\n";
    cout << "====================================\n";
    cout << "1. Order Management (CRUD)\n";
    cout << "2. Order Processing\n";
    cout << "3. Order Search\n";
    cout << "4. Order Statistics\n";
    cout << "0. Exit\n";
    cout << "====================================\n";
}
