#include "orderManager.h"
#include <cmath>

using namespace std;

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

    if (!isNotFutureDate(order.getNgay(), order.getThang(), order.getNam()))
        return false;

    if (!isfinite(total) || total < 0)
        return false;

    if (order.getTrangThai() != ChoPheDuyet || findOrderById(id) != nullptr)
        return false;

    orders.push_back(order);

    // Phần này để xử lý Queue.
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
