#include <iostream>
#include "orderManager.h"
using namespace std;

int OrderManager::getTotalOrders()
{
    int dem = 0;
    for (Node* p = queue.head; p != nullptr; p = p->next)
    {
        dem++;
    }
    return dem;
}

double OrderManager::getTotalValue()
{
    double tong = 0;
    for (Node* p = queue.head; p != nullptr; p = p->next)
    {
        tong += p->data.getTongTien();
    }
    return tong;
}

int OrderManager::countByStatus(Status status)
{
    int dem = 0;
    for (Node* p = queue.head; p != nullptr; p = p->next)
    {
        if (p->data.getTrangThai() == status)
        {
            dem++;
        }
    }
    return dem;
}

void OrderManager::getStatistics()
{
    cout << "Tong so don: " << getTotalOrders() << endl;
    cout << "Tong gia tri: " << getTotalValue() << endl;
    cout << "Cho phe duyet: " << countByStatus(ChoPheDuyet) << endl;
    cout << "Da duyet: " << countByStatus(DaDuyet) << endl;
    cout << "Huy: " << countByStatus(Huy) << endl;
    cout << "Hoan thanh: " << countByStatus(HoanThanh) << endl;
}