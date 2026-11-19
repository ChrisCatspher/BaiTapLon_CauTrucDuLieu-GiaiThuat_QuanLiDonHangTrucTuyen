#include "orderManager.h"
bool OrderManager::addOrderToQueue(string id)
{
    Order* order = findOrderById(id);
    if (order == nullptr || order->getTrangThai() != ChoPheDuyet)
        return false;

    pendingQueue.enqueue(id);
    return true;
}
void OrderManager::syncQueue()
{
    int n = pendingQueue.getSize();
    for (int i = 0; i < n; i++)
    {
        string id = pendingQueue.front();
        pendingQueue.dequeue();

        Order* order = findOrderById(id);
        if (order != nullptr && order->getTrangThai() == ChoPheDuyet)
            pendingQueue.enqueue(id);
    }
}
void OrderManager::processNext()
{
    syncQueue();

    if (pendingQueue.isEmpty())
    {
        cout << "Khong co don nao dang cho xu ly." << endl;
        return;
    }

    string id = pendingQueue.front();
    approveOrder(id);
    cout << "Da phe duyet don " << id << endl;
}

bool OrderManager::approveOrder(string id)
{
    syncQueue();

    if (pendingQueue.isEmpty() || pendingQueue.front() != id)
        return false;

    updateStatus(id, DaDuyet);
    pendingQueue.dequeue();
    return true;
}
bool OrderManager::cancelFrontOrder()
{
    syncQueue();

    if (pendingQueue.isEmpty())
        return false;

    updateStatus(pendingQueue.front(), Huy);
    pendingQueue.dequeue();
    return true;
}

bool OrderManager::cancelOrder(string id)
{
    if (!updateStatus(id, Huy))
        return false;

    syncQueue();
    return true;
}

bool OrderManager::completeOrder(string id)
{
   return updateStatus(id, HoanThanh);
}

bool OrderManager::updateStatus(string id, Status status)
{
     Order* order = findOrderById(id);
    if (order == nullptr)
        return false;

    Status current = order->getTrangThai();
    
    if (current == ChoPheDuyet && (status == DaDuyet || status == Huy))
    {
        order->setTrangThai(status);
        return true;
    }
    if (current == DaDuyet && status == HoanThanh)
    {
        order->setTrangThai(status);
        return true;
    }

    return false;
}
