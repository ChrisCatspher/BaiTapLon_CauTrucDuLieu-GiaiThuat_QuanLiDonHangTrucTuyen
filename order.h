#pragma once
#include <iostream>
#include <string>

using namespace std;

enum Status {
    ChoPheDuyet,
    DaDuyet,
    Huy,
    HoanThanh
};

class Order {
private:
    struct Date {
        int ngay, thang, nam;
    };

    string orderId;
    string customerName;
    Date createDate;
    double tongtien;
    Status trangthai;

public:
    Order(string id, string name, int ngay, int thang, int nam, double tongtien, Status trangthai);

    double getTongTien() const;
    Status getTrangThai() const;

    void setTrangThai(Status s);

    int getNgay() const;
    int getThang() const;
    int getNam() const;

    string getOrderId() const;
    string getCustomerName() const;

    string getTrangThaiText() const;
};