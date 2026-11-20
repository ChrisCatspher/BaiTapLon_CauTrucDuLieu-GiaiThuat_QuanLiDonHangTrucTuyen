#include "orderManager.h"

#include <algorithm>
#include <cmath>

namespace {
bool isValidDate(int day, int month, int year) {
    if (year < 1 || month < 1 || month > 12)
        return false;

    const int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    const bool leapYear = year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
    const int maxDay = daysInMonth[month - 1] + (month == 2 && leapYear);
    return day >= 1 && day <= maxDay;
}
}

bool OrderManager::addOrder(const Order& order) {
    const string id = order.getOrderId();
    const double total = order.getTongTien();

    if (id.find_first_not_of(" \t\n\r\f\v") == string::npos ||
        order.getCustomerName().find_first_not_of(" \t\n\r\f\v") == string::npos ||
        !isValidDate(order.getNgay(), order.getThang(), order.getNam()) ||
        !std::isfinite(total) || total < 0 ||
        order.getTrangThai() != ChoPheDuyet || findOrderById(id) != nullptr) {
        return false;
    }

    orders.push_back(order);

    // Xu ly Queue can tim thay don trong danh sach truoc khi enqueue.
    if (!addOrderToQueue(id)) {
        orders.pop_back();
        return false;
    }

    return true;
}

bool OrderManager::deleteOrder(string id) {
    const auto found = std::find_if(orders.begin(), orders.end(), [&id](const Order& order) {
        return order.getOrderId() == id;
    });
    if (found == orders.end())
        return false;

    orders.erase(found);
    syncQueue();
    return true;
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
    result.reserve(orders.size());
    for (Order& order : orders)
        result.push_back(&order);

    displayOrders(result);
}
