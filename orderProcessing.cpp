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
//bỏ bớt 1 lần syncqueue trong processNext vì ko cần thiết
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

//Queue chỉ xóa đơn khi việc cập nhật trạng thái thành công (sửa trong approverOrder và cancelFrontOrder)
bool OrderManager::approveOrder(string id)
{
    syncQueue();

    if (pendingQueue.isEmpty() || pendingQueue.front() != id)
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
