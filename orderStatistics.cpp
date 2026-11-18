
#include <iostream>
#include "orderManager.h"
using namespace std;

int OrderManager::getTotalOrders()
{
    return orders.size();
}

double OrderManager::getTotalValue()
{
    double tong = 0;

    for (int i = 0; i < orders.size(); i++)
    {
        tong += orders[i].getTongTien();
    }

    return tong;
}

int OrderManager::countByStatus(Status status)
{
    int dem = 0;

    for (int i = 0; i < orders.size(); i++)
    {
        if (orders[i].getTrangThai() == status)
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
