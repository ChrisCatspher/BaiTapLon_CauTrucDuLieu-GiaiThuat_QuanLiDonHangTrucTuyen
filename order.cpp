#include "order.h"

Order::Order(string id, string name, int ngay, int thang,
             int nam, double tongtien, Status trangthai) {
    orderId = id;
    customerName = name;
    createDate.ngay = ngay;
    createDate.thang = thang;
    createDate.nam = nam;
    this->tongtien = tongtien;
    this->trangthai = trangthai;
}

double Order::getTongTien() const {
    return tongtien;
}

Status Order::getTrangThai() const {
    return trangthai;
}

void Order::setTrangThai(Status s) {
    trangthai = s;
}

int Order::getNgay() const {
    return createDate.ngay;
}

int Order::getThang() const {
    return createDate.thang;
}

int Order::getNam() const {
    return createDate.nam;
}

string Order::getOrderId() const {
    return orderId;
}

string Order::getCustomerName() const {
    return customerName;
}

string Order::getTrangThaiText() const {
    switch (trangthai) {
        case ChoPheDuyet: return "Cho phe duyet";
        case DaDuyet: return "Da duyet";
        case Huy: return "Huy";
        case HoanThanh: return "Hoan thanh";
        default: return "Khong xac dinh";
    }
}