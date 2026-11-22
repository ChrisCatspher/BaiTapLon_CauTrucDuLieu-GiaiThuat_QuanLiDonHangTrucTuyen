#include "orderManager.h"
//đã có kiểm tra trùng trong orderqueue.cpp rồi nên ko cần kiếm tra lại nhiều
bool OrderManager::addOrderToQueue(string id)
{
    Order* order = findOrderById(id);
    if (order == nullptr || order->getTrangThai() != ChoPheDuyet)
        return false;

    syncQueue();
    if (pendingQueue.contains(id))
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
    if (pendingQueue.isEmpty())
    {
        cout << "Khong co don nao dang cho xu ly." << endl;
        return;
    }

    string id = pendingQueue.front();
    if (approveOrder(id))
        cout << "Da phe duyet don " << id << endl;
    else
        cout << "Khong the phe duyet don " << id << endl;
    
}

bool OrderManager::approveOrder(string id)
{
    if (pendingQueue.isEmpty() || pendingQueue.front() != id)
        return false;

    Order* order = findOrderById(id);

    if (order == nullptr || order->getTrangThai() != ChoPheDuyet)
        return false;

    if(!updateStatus(id, DaDuyet))
        return false;

    pendingQueue.dequeue();
    return true;
}

bool OrderManager::cancelFrontOrder()
{
    syncQueue();

    if (pendingQueue.isEmpty())
        return false;

    string id = pendingQueue.front();

    if (!updateStatus(id, Huy))
        return false;

    pendingQueue.dequeue();
    return true;
}

bool OrderManager::cancelOrder(string id)
{
    Order* order = findOrderById(id);

    if (order == nullptr)
        return false;

    Status current = order->getTrangThai();

    if (current != ChoPheDuyet && current != DaDuyet)
        return false;

    if (!updateStatus(id, Huy))
        return false;

    pendingQueue.remove(id);

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
    
    if (current == ChoPheDuyet)
    {
        if (status == DaDuyet || status == Huy) {
            order->setTrangThai(status);
            return true;
        }
    }

    if (current == DaDuyet) {
        if (status == HoanThanh || status == Huy) {
            order->setTrangThai(status);
            return true;
        }
    }

    return false;
}
