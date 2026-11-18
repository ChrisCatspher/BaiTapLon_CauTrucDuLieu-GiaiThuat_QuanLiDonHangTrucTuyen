#pragma once
#include <iostream>
#include <string>
using namespace std;

enum Status
{
    ChoPheDuyet,
    DaDuyet,
    Huy,
    HoanThanh
};

class Order {
private:
    struct Date
    {
        int ngay, thang, nam;
    };

    string orderId;
    string customerName;
    Date createDate;
    double tongtien;
    Status trangthai;

public:
    double getTongTien()
    {
        return tongtien;
    }

    Status getTrangThai()
    {
        return trangthai;
    }
};