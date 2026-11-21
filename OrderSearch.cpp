#include "orderManager.h"
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

bool  OrderManager::namNhuan(int nam) {
    return (nam % 400 == 0) || (nam % 4 == 0 && nam % 100 != 0);
}

bool  OrderManager::validateDate(int ngay, int thang, int nam) {
    if (nam < 1 || thang < 1 || thang > 12)
        return false;

    int soNgayTrongThang[] = {
        0, 31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };

    if (thang == 2 && namNhuan(nam))
        soNgayTrongThang[2] = 29;

    return ngay >= 1 && ngay <= soNgayTrongThang[thang];
}

string dateToString(int ngay, int thang, int nam) {
    string s = "";
    if (ngay < 10) s += "0";
    s += to_string(ngay) + "/";
    if (thang < 10) s += "0";
    s += to_string(thang) + "/" + to_string(nam);
    return s;
}

vector<Order*> OrderManager::findByDate(string date) {
    vector<Order*> result;

    for (Order& order : orders) {
        string orderDate = dateToString(
            order.getNgay(),
            order.getThang(),
            order.getNam()
        );

        if (orderDate == date) {
            result.push_back(&order);
        }
    }

    return result;
}

vector<Order*> OrderManager::findByStatus(Status status) {
    vector<Order*> result;

    for (Order& order : orders) {
        if (order.getTrangThai() == status) {
            result.push_back(&order);
        }
    }

    return result;
}

void OrderManager::displayOrders(const vector<Order*>& ds) {
    if (ds.empty()) {
        cout << "Khong tim thay don hang phu hop!\n";
        return;
    }

    cout << left << setw(13) << "Ngay tao"
         << setw(12) << "Ma don"
         << setw(16) << "Tong tien"
         << setw(22) << "Khach hang"
         << "Trang thai\n";

    cout << string(78, '-') << '\n';

    for (const Order* don : ds) {
        cout << left
             << setw(13) << dateToString(
                    don->getNgay(),
                    don->getThang(),
                    don->getNam()
                )
             << setw(12) << don->getOrderId()
             << setw(16) << fixed << setprecision(0)
             << don->getTongTien()
             << setw(22) << don->getCustomerName()
             << don->getTrangThaiText() << '\n';
    }
}

void OrderManager::displayByDate(string date) {
    displayOrders(findByDate(date));
}

void OrderManager::displayByStatus(Status status) {
    displayOrders(findByStatus(status));
}

// CODE CŨ
// void displayOrders(queue<Order> ds) {
//     if (ds.empty()) {
//         cout << "Khong tim thay don hang phu hop!\n";
//         return;
//     }

//     cout << left << setw(13) << "Ngay tao"
//          << setw(12) << "Ma don"
//          << setw(16) << "Tong tien"
//          << setw(22) << "Khach hang"
//          << "Trang thai\n";
//     cout << string(78, '-') << '\n';

//     while (!ds.empty()) {
//         Order don = ds.front();
//         ds.pop();

//         cout << left
//              << setw(13) << dateToString(don.getNgay(), don.getThang(), don.getNam())
//              << setw(12) << don.getOrderId()
//              << setw(16) << fixed << setprecision(0) << don.getTongTien()
//              << setw(22) << don.getCustomerName()
//              << don.getTrangThaiText() << '\n';
//     }
// }

// void searchByDate(queue<Order> ds, int ngay, int thang, int nam) {
//     if (!validateDate(ngay, thang, nam)) {
//         cout << "Ngay thang khong hop le!\n";
//         return;
//     }

//     queue<Order> ketQua;

//     while (!ds.empty()) {
//         Order don = ds.front();
//         ds.pop();

//         if (don.getNgay() == ngay &&
//             don.getThang() == thang &&
//             don.getNam() == nam) {
//             ketQua.push(don);
//         }
//     }

//     displayOrders(ketQua);
// }

// void filterByStatus(queue<Order> ds, int trangThaiCanTim) {
//     if (trangThaiCanTim < 0 || trangThaiCanTim > 3) {
//         cout << "Trang thai khong hop le!\n";
//         return;
//     }

//     queue<Order> ketQua;

//     while (!ds.empty()) {
//         Order don = ds.front();
//         ds.pop();

//         if (don.getTrangThai() == trangThaiCanTim)
//             ketQua.push(don);
//     }

//     displayOrders(ketQua);
// }
//////////////////////////////////////////////////////////////////




