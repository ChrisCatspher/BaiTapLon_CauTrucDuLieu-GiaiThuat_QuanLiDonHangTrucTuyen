#include "InputUtils.h"
#include <sstream>
#include <cmath>

int inputInt(string message) {
    int value;

    while (true) {
        cout << message;

        if (cin >> value) {
            cin.ignore(10000, '\n');
            return value;
        }

        cout << "Du lieu khong hop le! Vui long nhap so nguyen.\n";

        cin.clear();
        cin.ignore(10000, '\n');
    }
}

double inputDouble(string message) {
    string input;
    double value;

    while (true) {
        cout << message;
        getline(cin, input);

        stringstream ss(input);
        char extra;

        if ((ss >> value) && !(ss >> extra)
            && isfinite(value) && value >= 0) {
            return value;
        }

        cout << "Du lieu khong hop le! Vui long nhap so thuc khong am.\n";
    }
}

string inputString(string message) {
    string value;

    while (true) {
        cout << message;
        getline(cin, value);

        if (!value.empty()) return value;

        cout << "Du lieu khong duoc de trong! Vui long nhap lai.\n";
    }
}
