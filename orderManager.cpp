#include "orderManager.h"
#include <fstream>
#include <iomanip>
#include <sstream>

OrderManager::OrderManager()
{
}

OrderManager::~OrderManager()
{
}

bool OrderManager::isValidDate(int ngay, int thang, int nam) {
    if (nam < 1 || thang < 1 || thang > 12)
        return false;

    int soNgayTrongThang[] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };

    bool namNhuan = (nam % 400 == 0) ||
                    (nam % 4 == 0 && nam % 100 != 0);

    if (namNhuan)
        soNgayTrongThang[1] = 29;

    return ngay >= 1 && ngay <= soNgayTrongThang[thang - 1];
}

bool OrderManager::isNotFutureDate(int ngay, int thang, int nam) {
    time_t now = time(nullptr);
    tm* current = localtime(&now);

    if (current == nullptr) return false;

    int currentYear = current->tm_year + 1900;
    int currentMonth = current->tm_mon + 1;
    int currentDay = current->tm_mday;

    if (nam != currentYear)
        return nam < currentYear;

    if (thang != currentMonth)
        return thang < currentMonth;

    return ngay <= currentDay;
}


bool OrderManager::saveToFile(const string& filename) {
    ofstream file(filename);

    if (!file.is_open()) {
        cout << "Khong the mo file de luu du lieu!\n";
        return false;
    }

    file << "THONG KE DON DAT HANG\n";
    file << string(105, '=') << '\n';

    file << "Tong so don hang: " << getTotalOrders() << '\n';

    file << "Tong gia tri don hang: "
         << fixed << setprecision(2) << getTotalValue() << '\n';

    file << "So don cho phe duyet: "
         << countByStatus(ChoPheDuyet) << '\n';

    file << "So don da duyet: "
         << countByStatus(DaDuyet) << '\n';

    file << "So don bi huy: "
         << countByStatus(Huy) << '\n';

    file << "So don hoan thanh: "
         << countByStatus(HoanThanh) << '\n';

    file << string(105, '=') << "\n\n";


    file << "CHI TIET DANH SACH DON DAT HANG\n";
    file << string(105, '=') << '\n';

    file << left
         << setw(12) << "Ngay tao"
         << "| " << setw(15) << "Ma don hang"
         << "| " << setw(15) << "Tong tien"
         << "| " << setw(25) << "Ten khach hang"
         << "| " << "Trang thai\n";

    file << string(105, '=') << '\n';

    for (const Order& order : orders) {
        string ngayTao = to_string(order.getNgay()) + "/" +
                         to_string(order.getThang()) + "/" +
                         to_string(order.getNam());

        file << left
             << setw(12) << ngayTao
             << "| " << setw(15) << order.getOrderId()
             << "| " << setw(15) << fixed << setprecision(2)
             << order.getTongTien()
             << "| " << setw(25) << order.getCustomerName()
             << "| " << order.getTrangThaiText() << '\n';
    }

    file << string(105, '=') << '\n';

    file.close();
    return saveDataToFile("orders_data.txt");
}

bool OrderManager::saveDataToFile(const string& filename) {
    ofstream file(filename);

    if (!file.is_open()) {
        cout << "Khong the mo file de luu du lieu!\n";
        return false;
    }

    for (const Order& order : orders) {
        file << order.getOrderId() << "|"
             << order.getCustomerName() << "|"
             << order.getNgay() << "|"
             << order.getThang() << "|"
             << order.getNam() << "|"
             << order.getTongTien() << "|"
             << static_cast<int>(order.getTrangThai())
             << '\n';
    }

    file.close();
    return true;
}

bool OrderManager::loadFromFile(const string& filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        return false;
    }

    orders.clear();

    string line;

    while (getline(file, line)) {
        stringstream ss(line);

        string id, name;
        int ngay, thang, nam, status;
        double tien;
        char delimiter;

        if (!getline(ss, id, '|') ||
            !getline(ss, name, '|') ||
            !(ss >> ngay >> delimiter) || delimiter != '|' ||
            !(ss >> thang >> delimiter) || delimiter != '|' ||
            !(ss >> nam >> delimiter) || delimiter != '|' ||
            !(ss >> tien >> delimiter) || delimiter != '|' ||
            !(ss >> status)) {
            continue;
        }

        if (status < ChoPheDuyet || status > HoanThanh)
            continue;

        if (!isValidDate(ngay, thang, nam) ||
            tien < 0 || id.empty() || name.empty())
            continue;

        Order order(
            id, name, ngay, thang, nam,
            tien, static_cast<Status>(status)
        );

        orders.push_back(order);
    }

    file.close();
    return true;
}