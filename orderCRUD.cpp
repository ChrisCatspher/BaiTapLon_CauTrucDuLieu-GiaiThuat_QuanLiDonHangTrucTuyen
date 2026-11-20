#include "orderManager.h"
#include <cmath>

namespace {
bool isValidDate(int day, int month, int year) {
    if (year < 1 || month < 1 || month > 12)
        return false;

    const int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    const bool leapYear = year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
    int maxDay = daysInMonth[month - 1];
    if (month == 2 && leapYear)
        maxDay = 29;
    return day >= 1 && day <= maxDay;
}
}

bool OrderManager::addOrder(const Order& order) {
    const string id = order.getOrderId();
    const double total = order.getTongTien();

    const string khoangTrang = " \t\n\r\f\v";
    if (id.find_first_not_of(khoangTrang) == string::npos ||
        order.getCustomerName().find_first_not_of(khoangTrang) == string::npos) {
        return false;
    }

    if (!isValidDate(order.getNgay(), order.getThang(), order.getNam()))
        return false;

    if (!std::isfinite(total) || total < 0)
        return false;

    if (order.getTrangThai() != ChoPheDuyet || findOrderById(id) != nullptr)
        return false;

    orders.push_back(order);

    // Xu ly Queue can tim thay don trong danh sach truoc khi enqueue.
    if (!addOrderToQueue(id)) {
        orders.pop_back();
        return false;
    }

    return true;
}

bool OrderManager::deleteOrder(string id) {
    for (auto it = orders.begin(); it != orders.end(); ++it) {
        if (it->getOrderId() == id) {
            orders.erase(it);
            // Bo ma don vua xoa khoi Queue neu don con dang cho.
            syncQueue();
            return true;
        }
    }

    return false;
}

Order* OrderManager::findOrderById(string id) {
    for (Order& order : orders) {
        if (order.getOrderId() == id)
            return &order;
    }

    return nullptr;
}

void OrderManager::displayOrder(string id) {
    Order* order = findOrderById(id);
    if (order == nullptr) {
        cout << "Khong tim thay don hang co ma " << id << "!\n";
        return;
    }

    displayOrders({order});
}

void OrderManager::displayAllOrders() {
    if (orders.empty()) {
        cout << "Danh sach don hang dang rong!\n";
        return;
    }

    vector<Order*> result;
    for (Order& order : orders)
        result.push_back(&order);

    displayOrders(result);
}
