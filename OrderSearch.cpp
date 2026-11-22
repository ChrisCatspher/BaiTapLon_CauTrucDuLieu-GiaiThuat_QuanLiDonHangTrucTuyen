#include "orderManager.h"
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

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
