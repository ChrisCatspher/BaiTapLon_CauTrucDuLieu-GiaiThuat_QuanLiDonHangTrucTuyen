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
