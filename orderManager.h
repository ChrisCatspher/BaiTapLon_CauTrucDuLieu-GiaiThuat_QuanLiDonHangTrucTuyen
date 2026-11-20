
#ifndef ORDER_MANAGER_H
#define ORDER_MANAGER_H

#include <iostream>
#include <string>
#include <vector>
#include "order.h"
#include "orderqueue.h"

using namespace std;
class OrderManager {
private:
    vector<Order> orders;
    OrderQueue pendingQueue;

public:
    OrderManager();
    ~OrderManager();

    // CRUD - Thanh vien 2
    bool addOrder(const Order& order);
    bool deleteOrder(string id);
    Order* findOrderById(string id);
    void displayOrder(string id);
    void displayAllOrders();

    // Processing - Thanh vien 3
    void processNext();
    bool approveOrder(string id);
    bool cancelOrder(string id);
    bool completeOrder(string id);
    bool updateStatus(string id, Status status);
    bool addOrderToQueue(string id);
    void syncQueue();
    bool cancelFrontOrder();

    // Search - Thanh vien 4 - finished
    vector<Order*> findByDate(string date);
    vector<Order*> findByStatus(Status status);
    void displayByDate(string date);
    void displayByStatus(Status status);
    void displayOrders(const vector<Order*>& ds);

    // Statistics - Thanh vien 5
    int getTotalOrders();
    double getTotalValue();
    int countByStatus(Status status);
    void getStatistics();
};

#endif
